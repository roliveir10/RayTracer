/*static float			hyperboloid(__constant t_object *obj, const t_ray *ray)
{
	float3				tmp;
	float2				sol;

	tmp.x = ray->dir.x * ray->dir.x - ray->dir.y * ray->dir.y + ray->dir.z * ray->dir.z;
	tmp.y = 2.f * (ray->dir.x * ray->o.x - ray->dir.y * ray->o.y + ray->dir.z * ray->o.z);
	tmp.z = ray->o.x * ray->o.x - ray->o.y * ray->o.y + ray->o.z * ray->o.z - 1.f;

	sol = ft_2nd_degree(tmp.x, tmp.y, tmp.z);
	if (obj->isLimited)
		return (limit(ray, sol, obj->limit));
	return (lowerDist(sol));
}*/
