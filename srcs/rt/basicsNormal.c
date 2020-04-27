#include <math.h>
#include "rt.h"

static t_vector				sphereNormal(t_rayHit hit)
{
	return (hit.point);
}

static t_vector				planNormal(__unused t_rayHit hit)
{
	t_vector				normal;

	ft_bzero(&normal, sizeof(t_vector));
	normal.y = 1;
	return (normal);
}

static t_vector				cylindreNormal(t_rayHit hit)
{
	t_vector				normal;
	double					denominator;

	denominator = sqrt(pow(hit.point.x, 2) + pow(hit.point.z, 2));
	normal.x = hit.obj.radius * (hit.point.x / denominator);
	normal.z = hit.obj.radius * (hit.point.z / denominator);
	return (normal);
}

static t_vector				coneNormal(t_rayHit hit)
{
	t_vector				normal;
	double					neg;
	double					tanAngle;

	neg = hit.point.y <= 0 ? 1 : -1;
	tanAngle = tan(hit.obj.angle * 0.5) * neg;
	normal = ft_normalize(hit.point);
	normal.x /= tanAngle;
	normal.y = tanAngle;
	normal.z /= tanAngle;
	return (normal);
}

static t_vector				boxNormal(t_rayHit hit)
{
	t_vector			normal;

	ft_bzero(&normal, sizeof(t_vector));
	if (hit.point.z < hit.obj.b[0].z + 1e-5)
		normal.z = -1;
	else if (hit.point.y > hit.obj.b[1].y - 1e-5)
		normal.y = -1;
	else if (hit.point.y < hit.obj.b[0].y + 1e-5)
		normal.y = -1;
	else if (hit.point.x > hit.obj.b[1].x - 1e-5)
		normal.x = -1;
	else if (hit.point.x < hit.obj.b[0].x + 1e-5)
		normal.x = -1;
	else if (hit.point.z > hit.obj.b[1].z - 1e-5)
		normal.z = -1;

			return (normal);
}

t_vector					normal(t_rayHit hit)
{
	t_vector				(*func[NBR_SHAPE])(t_rayHit) = {
		sphereNormal, planNormal, cylindreNormal, coneNormal, boxNormal};
	
	hit.point = changePointReference(hit.point, hit.obj);
	return (ft_normalize(func[hit.obj.type](hit)));
}
