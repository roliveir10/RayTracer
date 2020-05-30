static t_intersection	infCylindre(float *t, t_ray *ray, t_bbox aabb)
{
	float3				quad;
	float2				roots;

	quad.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z;
	quad.y = 2.f * (ray->dir.x * ray->o.x + ray->dir.z * ray->o.z);
	quad.z = ray->o.x * ray->o.x + ray->o.z * ray->o.z - 1.f;
	if (!ft_2nd_degree(&roots, quad))
		return (NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (NONE);
	else if (roots.x <= 0.f)
	{
		*t = roots.y;
		return (hitPosInBbox(ray->o + roots.y * ray->dir, aabb) ? INSIDE : NONE);
	}
	else if (roots.y <= 0.f)
	{
		*t = roots.x;
		return (hitPosInBbox(ray->o + roots.x * ray->dir, aabb) ? INSIDE : NONE);
	}
	*t = fmin(roots.x, roots.y);
	if (hitPosInBbox(ray->o + (*t) * ray->dir, aabb))
		return (OUTSIDE);
	*t = fmax(roots.x, roots.y);
	return (hitPosInBbox(ray->o + (*t) * ray->dir, aabb) ? INSIDE : NONE);
}

static t_intersection		plan(float *t, t_ray *ray, t_bbox aabb)
{
	float					tmp;
	t_intersection			inter;

	if (ray->o.y * ray->dir.y >= 0.f)
		return (NONE);
	if ((tmp = -ray->o.y / ray->dir.y) >= ray->t)
		return (NONE);
	*t = tmp;
	inter = ray->o.y > 0.f ? OUTSIDE : INSIDE;
	return (hitPosInBbox(ray->o + tmp * ray->dir, aabb) ? inter : NONE);
}

static float		disk(float *t, t_ray *ray, t_bbox aabb)
{
	float3			tmp;
	t_intersection	inter;
	float			dist;

	inter = plan(t, ray, aabb);
	if (inter)
	{
		dist = *t;
		tmp.x = ray->o.x + dist * ray->dir.x;
		tmp.z = ray->o.z + dist * ray->dir.z;
		if (tmp.x * tmp.x + tmp.z * tmp.z <= 1.f)
		{
			*t = dist;
			return (inter);
		}
	}
	return (NONE);
}

static t_intersection		rectangle(float *t, t_ray *ray, t_bbox aabb)
{
	float3					tmp;
	t_intersection			inter;
	float					dist;

	inter = plan(t, ray, aabb);
	if (inter)
	{
		dist = *t;
		tmp.x = ray->o.x + dist * ray->dir.x;
		tmp.z = ray->o.z + dist * ray->dir.z;
		if (-1.f <= tmp.x && tmp.x <= 1.f && -1.f <= tmp.z && tmp.z <= 1.f)
			return (inter);
	}
	return (NONE);
}

static t_intersection		triangle(float *t, t_ray *ray, t_bbox aabb)
{
	float3					tmp;
	float					tmpz;
	t_intersection			inter;
	float					dist;

	inter = plan(t, ray, aabb);
	if (inter)
	{
		dist = *t;
		tmp.x = ray->o.x + dist * ray->dir.x;
		tmp.z = ray->o.z + dist * ray->dir.z;
		tmpz = tmp.z * 0.5f;
		if (0.f <= tmp.z && tmp.z <= 1.f && -tmpz <= tmp.x && tmp.x <= tmpz)
			return (inter);	
	}
	return (NONE);
}

static t_intersection		cylindre(float *t, t_ray *ray, t_bbox aabb)
{
	t_ray					tmpRay;
	float					tmp;
	t_intersection			inter = NONE;

	tmp = ray->t;
	tmpRay = *ray;
	tmpRay.interType = infCylindre(t, ray, aabb);
	if (tmpRay.interType)
	{
		tmp = *t;
		inter = tmpRay.interType;
	}
	tmpRay.o.y -= 1.f;
	aabb.vmin.y -= 1.f;
	aabb.vmax.y -= 1.f;
	tmpRay.interType = disk(t, &tmpRay, aabb);
	if (tmpRay.interType && *t < tmp)
	{
		tmp = *t;
		inter = inter ? -inter : tmpRay.interType;
	}
	tmpRay.o.y += 2.f;
	aabb.vmin.y += 2.f;
	aabb.vmax.y += 2.f;
	tmpRay.interType = -disk(t, &tmpRay, aabb);
	if (tmpRay.interType && *t < tmp)
	{
			tmp = *t;
			inter = inter ? -inter : tmpRay.interType;
	}
	*t = tmp;
	return (inter);
}

static t_intersection		sphere(float *t, t_ray *ray, t_bbox aabb)
{
	float3					quad;
	float2					roots;

	quad.x = dot(ray->dir, ray->dir);
	quad.y = 2.f * dot(ray->dir, ray->o);
	quad.z = dot(ray->o, ray->o) - 1.f;
	if (!ft_2nd_degree(&roots, quad))
		return (NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (NONE);
	else if (roots.x <= 0.f)
	{
		*t = roots.y;
		return (hitPosInBbox(ray->o + roots.y * ray->dir, aabb) ? INSIDE : NONE);
	}
	else if (roots.y <= 0.f)
	{
		*t = roots.x;
		return (hitPosInBbox(ray->o + roots.x * ray->dir, aabb) ? INSIDE : NONE);
	}
	*t = fmin(roots.x, roots.y);
	if (hitPosInBbox(ray->o + (*t) * ray->dir, aabb))
		return (OUTSIDE);
	*t = fmax(roots.x, roots.y);
	return (hitPosInBbox(ray->o + (*t) * ray->dir, aabb));
}

static t_intersection		infCone(float *t, t_ray *ray, t_bbox aabb)
{
	float3					quad;
	float2					roots;
	bool					hrzOrient;
	t_intersection			inter;

	quad.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z
			- ray->dir.y * ray->dir.y;
	quad.y = 2.f * (ray->dir.x * ray->o.x + ray->dir.z * ray->o.z
				- ray->dir.y * ray->o.y);
	quad.z = ray->o.x * ray->o.x + ray->o.z * ray->o.z
			- ray->o.y * ray->o.y;
	if (!ft_2nd_degree(&roots, quad))
		return (NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (NONE);
	hrzOrient = ((ray->dir.y * roots.x + ray->o.y)
			* (ray->dir.y * roots.y + ray->o.y) >= 0.f);
	if (roots.x <= 0.f)
	{
		*t = roots.y;
		inter = hrzOrient ? INSIDE : OUTSIDE;
		return (hitPosInBbox(ray->o + roots.y * ray->dir, aabb) ? inter : NONE);
	}
	else if (roots.y <= 0.f)
	{
		*t = roots.x;
		inter = hrzOrient ? INSIDE : OUTSIDE;
		return (hitPosInBbox(ray->o + roots.x * ray->dir, aabb) ? inter : NONE);
	}
	*t = fmin(roots.x, roots.y);
	if (hitPosInBbox(ray->o + (*t) * ray->dir, aabb))
		return (hrzOrient ? OUTSIDE : INSIDE);
	*t = fmax(roots.x, roots.y);
	inter = hrzOrient ? INSIDE : OUTSIDE;
	return (hitPosInBbox(ray->o + (*t) * ray->dir, aabb) ? inter : NONE);
}

static t_intersection		cone(float *t, t_ray *ray, t_bbox aabb)
{
	t_ray					tmpRay;
	float					tmp;
	t_intersection			inter = NONE;

	tmp = ray->t;
	tmpRay = *ray;
	tmpRay.interType = infCone(t, ray, aabb);
	if (tmpRay.interType)
	{
		tmp = *t;
		inter = tmpRay.interType;
	}
	tmpRay.o.y += 1.f;
	aabb.vmin.y += 1.f;
	aabb.vmax.y += 1.f;
	tmpRay.interType = disk(t, &tmpRay, aabb);
	if (tmpRay.interType && *t < tmp)
	{
		tmp = *t;
		inter = inter ? -inter : tmpRay.interType;
	}
	*t = tmp;
	return (inter);
}

/*static t_intersection		cube(float *t, t_ray *ray, t_bbox aabb)
{
	float					tmin = 0.f;
	float					tmax = ray->t;
	t_bbox					laabb = (t_bbox){
					(float3){-1.f, -1.f, -1.f},
					(float3){1.f, 1.f, 1.f}
	};

	float3					invDir = native_recip(ray->dir);
	float3					ti = (laabb.vmin - ray->o) * invDir;
	float3					tf = (laabb.vmax - ray->o) * invDir;
	float3					tinf = fmin(ti, tf);
	float3					tsup = fmax(ti, tf);

	tmin = fmax(tmin, fmax(tinf.x, fmax(tinf.y, tinf.z)));
	tmax = fmin(tmax, fmin(tsup.x, fmin(tsup.y, tsup.z)));

	if (tmax <= 0.f || tmin > tmax)
		return (NONE);
	if (tmin <= 0.f)
	{
		*t = tmax;
		return (hitPosInBbox(ray->o + tmax * ray->dir, aabb) ? INSIDE : NONE);
	}
	*t = fmin(tmin, tmax);
	if (hitPosInBbox(ray->o + (*t) * ray->dir, aabb))
		return (OUTSIDE);
	*t = fmax(tmin, tmax);
	return (hitPosInBbox(ray->o + (*t) * ray->dir, aabb) ? INSIDE : NONE);
}
*/
static t_intersection		cube(float *t, t_ray *ray, t_bbox aabb, float radius)
{
	float					tmin = 0.f;
	float					tmax = ray->t;
	float3					invDir = native_recip(ray->dir);
	float3					n = invDir * ray->o;
	float3					k = fabs(invDir) * (1.f + radius);
	float3					t1 = -n - k;
	float3					t2 = -n + k;
	
	tmin = fmax(tmin, fmax(t1.z, fmax(t1.x, t1.y)));
	tmax = fmin(tmax, fmin(t2.z, fmin(t2.x, t2.y)));

	if (tmax <= 0.f || tmin > tmax)
		return (NONE);
	if (tmin <= 0.f)
	{
		*t = tmax;
		return (hitPosInBbox(ray->o + tmax * ray->dir, aabb) ? INSIDE : NONE);
	}
	*t = fmin(tmin, tmax);
	if (hitPosInBbox(ray->o + (*t) * ray->dir, aabb))
		return (OUTSIDE);
	*t = fmax(tmin, tmax);
	return (hitPosInBbox(ray->o + (*t) * ray->dir, aabb) ? INSIDE : NONE);
}

/*static t_intersection		roundedBox(float *t, t_ray *ray, t_bbox aabb)
{
	float3					invDir = native_recip(ray->dir);
	float3					n = invDir * ray->o;
	float					rad = 0.2f;
	float3					k = fabs(invDir) * (1.f + rad);
	float3					t1 = -n - k;
	float3					t2 = -n + k;
	float					tmin = fmax(fmax(t1.x, t1.y), t1.z);
	float					tmax = fmin(fmin(t2.x, t2.y), t2.z);
	t_ray					tmpRay = *ray;

	if (tmin > tmax || tmax < 0.f)
		return (NONE);
	*t = tmin;

	float3					hitPos = ray->o + tmin * ray->dir;
	float3					s = sign(hitPos);

	tmpRay.o *= s;
	tmpRay.dir *= s;
	hitPos *= s;

	//faces
	hitPos -= 1.f;
	hitPos = fmax(hitPos.xyz, hitPos.yzx);
	if (fmin(fmin(hitPos.x, hitPos.y), hitPos.z) < 0.f)
		return (OUTSIDE);
	float3					oc = tmpRay.o - 1.f;
	float3					dd = tmpRay.dir * tmpRay.dir;
	float3					oo = oc * oc;
	float3					od = oc * tmpRay.dir;
	float					ra2 = rad * rad;
	float					a;
	float					b;
	float					c;
	float					h;
	
	*t = ray->t;
	//corner
	b = od.x + od.y + od.z;
	c = oo.x + oo.y + oo.z - ra2;
	h = b * b - c;
	if (h > 0.f)
	{
		*t = -b - sqrt(h);
		printf("%f %f %f\n", oc.x, oc.y, oc.z);
	}
	
	// edge X
	a = dd.y + dd.z;
	b = od.y + od.z;
	c = oo.y + oo.z - ra2;
	h = b * b - a * c;
	if (h > 0.f)
	{
		h = (-b - sqrt(h)) / a;
		if (h > 0.f && h < *t && fabs(tmpRay.o.x + tmpRay.dir.x * h) < 1.f)
			*t = h;
	}
	
	// edge Y
	a = dd.z + dd.x;
	b = od.z + od.x;
	c = oo.z + oo.x - ra2;
	h = b * b - a * c;
	if (h > 0.f)
	{
		h = (-b - sqrt(h)) / a;
		if (h > 0.f && h < *t && fabs(tmpRay.o.y + tmpRay.dir.y * h) < 1.f)
			*t = h;
	}
	
	// edge Z
	a = dd.x + dd.y;
	b = od.x + od.y;
	c = oo.x + oo.y - ra2;
	h = b * b - a * c;
	if (h > 0.f)
	{
		h = (-b - sqrt(h)) / a;
		if (h > 0.f && h < *t && fabs(tmpRay.o.z + tmpRay.dir.z * h) < 1.f)
			*t = h;
	}
	if (*t != ray->t)
		return (OUTSIDE);
	return (NONE);
}*/

static t_intersection		infHyperboloid(float *t, t_ray *ray, t_bbox aabb)
{
	float3					quad;
	float2					roots;
	t_intersection			inter;

	quad.x = ray->dir.x * ray->dir.x + ray->dir.z * ray->dir.z - ray->dir.y * ray->dir.y;
	quad.y = 2.f * (ray->dir.x * ray->o.x + ray->dir.z * ray->o.z - ray->dir.y * ray->o.y);
	quad.z = ray->o.x * ray->o.x + ray->o.z * ray->o.z - ray->o.y * ray->o.y - 1.f;
	if (!ft_2nd_degree(&roots, quad))
		return (NONE);
	if (roots.x <= 0.f && roots.y <= 0.f)
		return (NONE);
	inter = quad.z <= 0.f ? INSIDE : OUTSIDE;
	if (roots.x <= 0.f)
	{
		*t = roots.y;
		return (hitPosInBbox(ray->o + roots.y * ray->dir, aabb) ? inter : NONE);
	}
	else if (roots.y <= 0.f)
	{
		*t = roots.x;
		return (hitPosInBbox(ray->o + roots.x * ray->dir, aabb) ? inter : NONE);
	}
	*t = fmin(roots.x, roots.y);
	if (hitPosInBbox(ray->o + (*t) * ray->dir, aabb))
		return (inter);
	*t = fmax(roots.x, roots.y);
	return (hitPosInBbox(ray->o + (*t) * ray->dir, aabb) ? inter : NONE);
}

static t_intersection		primitiveIntersection
(
	float					*new_t,
	t_ray					*rayOs,
	t_objType				type,
	t_bbox					aabb
)
{
	t_intersection			inter;

	if (type == SPHERE)
		inter = sphere(new_t, rayOs, aabb);
	else if (type == PLAN)
		inter = plan(new_t, rayOs, aabb);
	else if (type == DISK)
		inter = disk(new_t, rayOs, aabb);
	else if (type == INFCYLINDRE)
		inter = infCylindre(new_t, rayOs, aabb);
	else if (type == CYLINDRE)
		inter = cylindre(new_t, rayOs, aabb);
	else if (type == INFCONE)
		inter = infCone(new_t, rayOs, aabb);
	else if (type == CONE)
		inter = cone(new_t, rayOs, aabb);
	else if (type == CUBE)
		inter = cube(new_t, rayOs, aabb, 0.f);
	else if (type == RECTANGLE)
		inter = rectangle(new_t, rayOs, aabb);
	else if (type == TRIANGLE)
		inter = triangle(new_t, rayOs, aabb);
	else if (type == INFHYPERBOLOID)
		inter = infHyperboloid(new_t, rayOs, aabb);
//	else if (type == ROUNDEDBOX)
//		inter = roundedBox(new_t, rayOs, aabb);
	else
		inter = NONE;
	return (inter);
}
