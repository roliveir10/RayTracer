#include <math.h>
#include "rt.h"

double				box(t_object obj, t_ray r)
{
	t_vector		*b;
	float			tmin, tmax, tymin, tymax, tzmin, tzmax;
	t_solution		sol;

	changeReference(&r, obj);
	b = obj.b;
	tmin = (b[r.sign[0]].x - r.o.x) * r.invDir.x;
	tmax = (b[1 - r.sign[0]].x - r.o.x) * r.invDir.x;
	tymin = (b[r.sign[1]].y - r.o.y) * r.invDir.y;
	tymax = (b[1 - r.sign[1]].y - r.o.y) * r.invDir.y;
	if (tmin > tymax || tymin > tmax)
		return (-1);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (b[r.sign[2]].z - r.o.z) * r.invDir.z;
	tzmax = (b[1 - r.sign[2]].z - r.o.z) * r.invDir.z;
	if (tmin > tzmax || tzmin > tmax)
		return (-1);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	if (tmin <= 0 && tmax <= 0)
		return (-1);
	sol.nbrSol = 2;
	sol.sol[0] = tmin;
	sol.sol[1] = tmax;
	if (obj.isLimited)
		return (limit(r, sol, obj));
	return (lowerDist(sol));
}
