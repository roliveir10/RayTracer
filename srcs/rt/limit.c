#include "rt.h"

static double			hitLimit(t_vector hitPos, t_limit limit, double dist)
{
	if (limit.sizeX > 0)
		if (hitPos.x <= limit.x || hitPos.x >= limit.x + limit.sizeX)
			return (-1);
	if (limit.sizeY > 0)
		if (hitPos.y <= limit.y || hitPos.y >= limit.y + limit.sizeY)
			return (-1);
	if (limit.sizeZ > 0)
		if (hitPos.z <= limit.z || hitPos.z >= limit.z + limit.sizeZ)
			return (-1);
	return (dist);
}

double				limit(t_ray ray, t_solution sol, t_object obj)
{
	t_vector		hitPos;
	t_limit			limit;
	double			distTmp;
	double			dist;

	dist = -1;
	if (sol.sol[0] <= 0 && sol.sol[1] <= 0)
		return (-1);
	limit = obj.limit;	
	hitPos = hitPoint(ray, sol.sol[0]);
	if (sol.nbrSol == 1)
		return (hitLimit(hitPos, limit, sol.sol[0]));
	for (int i = 0; i < sol.nbrSol; i++)
	{
		hitPos = hitPoint(ray, sol.sol[i]);
		distTmp = hitLimit(hitPos, limit, sol.sol[i]);
		if (distTmp > 0 && (dist == -1 || distTmp < dist))
			dist = distTmp;
	}
	return (dist);
}
