static bool						hitPosInBbox(float3 pos, t_bbox aabb)
{
	return (aabb.vmin.x - EPSILON < pos.x && pos.x < aabb.vmax.x + EPSILON
				&& aabb.vmin.y - EPSILON < pos.y && pos.y < aabb.vmax.y + EPSILON
				&& aabb.vmin.z - EPSILON < pos.z && pos.z < aabb.vmax.z + EPSILON);
}

static t_intersection			interBbox
(
			t_ray				ray,
			t_bbox				aabb,
			float				tmin,
			float				tmax,
			float				*t
)
{
	t_intersection				inter;
	float						tmaxOld = tmax;
	float3						invDir = native_recip(ray.dir);
	float3						ti = (aabb.vmin - ray.o) * invDir;
	float3						tf = (aabb.vmax - ray.o) * invDir;

	float3						tinf = fmin(ti, tf);
	float3						tsup = fmax(ti, tf);

	tmin = fmax(tmin, fmax(tinf.x, fmax(tinf.y, tinf.z)));
	tmax = fmin(tmax, fmin(tsup.x, fmin(tsup.y, tsup.z)));

	inter = tmin < tmax ? OUTSIDE : NONE;
	*t = inter ? tmin : tmaxOld;
	if (*t < EPSILON)
	{
		*t = tmax;
		inter = INSIDE;
	}
	return (inter);
}
