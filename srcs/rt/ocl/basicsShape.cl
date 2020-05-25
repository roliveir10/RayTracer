/*static float	lowerDist(const float2 sol)
{
	float		dist;

	dist = 1e6;
	if (sol.x <= 0 && sol.y <= 0)
		return (-1.f);
	if (sol.x > 0.f && sol.x < dist)
		dist = sol.x;
	if (sol.y > 0.f && sol.y < dist)
		dist = sol.y;
	return (dist);
}
*/
static t_intersection		plan(float *t, t_ray *ray)
{
	float					tmp;

	if (ray->o.y * ray->dir.y >= 0.f)
		return (NONE);
	if ((tmp = -ray->o.y / ray->dir.y) >= ray->t)
		return (NONE);
	*t = tmp;
	return (ray->o.y > 0.f ? OUTSIDE : INSIDE);

/*	if (ray->dir.y)
	{
		sol.x = -ray->o.y / ray->dir.y;
		if (obj->isLimited)
			return (limit(ray, sol, obj->limit));
		return (sol.x);
	}
	return (-1.f);
*/
}

static t_intersection		sphere(float *t, t_ray *ray)
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
		return (INSIDE);
	}
	else if (roots.y <= 0.f)
	{
		*t = roots.x;
		return (INSIDE);
	}
	else
	{
		*t = fmin(roots.x, roots.y);
		return (OUTSIDE);
	}
	/*if (obj->isLimited)
		return (limit(ray, sol, obj->limit));
	return (lowerDist(sol));
*/
}

static t_intersection	cylindre(float *t, t_ray *ray)
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
		return (INSIDE);
	}
	else if (roots.y <= 0.f)
	{
		*t = roots.x;
		return (INSIDE);
	}
	else
	{
		*t = fmin(roots.x, roots.y);
		return (OUTSIDE);
	}
}
/*
static float		disk(__constant t_object *obj, const t_ray *ray)
{
	float			dist = plan(obj, ray);
	float3			hitPoint;

	if (dist <= 0.f)
		return (-1.f);
	hitPoint.x = ray->o.x + dist * ray->dir.x;
	hitPoint.z = ray->o.z + dist * ray->dir.z;
	if (hitPoint.x * hitPoint.x + hitPoint.z * hitPoint.z <= 1.f)
		return (dist);
	return (-1.f);
}

static float		cone(__constant t_object *obj, const t_ray *ray)
{
	float			a;
	float			b;
	float			c;
	float2			sol;
	float			tanAngle;

	tanAngle = tan(obj->angle);
	a = pow(ray->dir.x, 2) + pow(ray->dir.z, 2) - pow(ray->dir.y * tanAngle, 2);
	b = 2.f * (ray->dir.x * ray->o.x + ray->dir.z * ray->o.z - ray->dir.y * tanAngle * ray->o.y * tanAngle);
	c = pow(ray->o.x, 2) + pow(ray->o.z, 2) - pow(ray->o.y * tanAngle, 2);
	sol = ft_2nd_degree(a, b, c);
	if (obj->isLimited)
		return (limit(ray, sol, obj->limit));
	return (lowerDist(sol));
}

static float	box(__constant t_object *obj, const t_ray *ray)
{
	float3		tmin;
	float3		tmax;
	float2		sol;

	float3		invDir = native_recip(ray->dir);
	int3		sign = (int3){(invDir.x < 0.f), (invDir.y < 0.f), (invDir.z < 0.f)};

	tmin.x = (obj->bbox[sign.x].x - ray->o.x) * invDir.x;
	tmax.x = (obj->bbox[1 - sign.x].x - ray->o.x) * invDir.x;
	tmin.y = (obj->bbox[sign.y].y - ray->o.y) * invDir.y;
	tmax.y = (obj->bbox[1 - sign.y].y - ray->o.y) * invDir.y;
	if (tmin.x > tmax.y || tmin.y > tmax.x)
		return (-1.f);
	if (tmin.y > tmin.x)
		tmin.x = tmin.y;
	if (tmax.y < tmax.x)
		tmax.x = tmax.y;
	tmin.z = (obj->bbox[sign.z].z - ray->o.z) * invDir.z;
	tmax.z = (obj->bbox[1 - sign.z].z - ray->o.z) * invDir.z;
	if (tmin.x > tmax.z || tmin.z > tmax.x)
		return (-1.f);
	if (tmin.z > tmin.x)
		tmin.x = tmin.z;
	if (tmax.z < tmax.x)
		tmax.x = tmax.z;
	if (tmin.x <= 0.f && tmax.x <= 0.f)
		return (-1.f);
	sol.x = tmin.x;
	sol.y = tmax.x;
	if (obj->isLimited)
		return (limit(ray, sol, obj->limit));
	return (lowerDist(sol));
}*/
