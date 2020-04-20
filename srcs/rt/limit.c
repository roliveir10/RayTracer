#include "rt.h"

double				limit(t_vector o, t_vector dir, double dist, t_object obj)
{
	t_vector		hitPos;
	t_limit			limit;

	if (dist < 0)
		return (dist);
	limit = obj.limit;
	hitPos = hitPoint(o, dir, dist);
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
