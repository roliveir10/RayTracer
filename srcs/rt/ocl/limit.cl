/*static float			hitLimit(float3 hitPos, t_limit limit, float dist)
{
	if (limit.size.x > 0)
		if (hitPos.x <= limit.origin.x || hitPos.x >= limit.origin.x + limit.size.x)
			return (-1.0);
	if (limit.size.y > 0)
		if (hitPos.y <= limit.origin.y || hitPos.y >= limit.origin.y + limit.size.y)
			return (-1.0);
	if (limit.size.z > 0)
		if (hitPos.z <= limit.origin.z || hitPos.z >= limit.origin.z + limit.size.z)
			return (-1.0);
	return (dist);
}

static float		limit(const t_ray *ray, const float2 sol, t_limit limit)
{
	float			distTmp;
	float			dist;

	dist = 1e8;
	if (sol.x <= 0.f && sol.y <= 0.f)
		return (-1.f);
	if (sol.y <= 0.f)
		return (hitLimit(ray->o + ray->dir * sol.x, limit, sol.x));
	if (sol.x <= 0.f)
		return (hitLimit(ray->o + ray->dir * sol.y, limit, sol.y));
	distTmp = hitLimit(ray->o + ray->dir * sol.x, limit, sol.x);
	if (distTmp > 0.f && distTmp < dist)
		dist = distTmp;
	distTmp = hitLimit(ray->o + ray->dir * sol.y, limit, sol.y);
	if (distTmp > 0.f && distTmp < dist)
		dist = distTmp;
	return (dist);
}*/
