#include <math.h>
#include "rt.h"

static t_vector				sphereNormal(t_vector point, __unused t_object obj)
{
	return (ft_normalize(point));
}

static t_vector				planNormal(__unused t_vector point, __unused t_object obj)
{
	t_vector				normal;

	ft_bzero(&normal, sizeof(t_vector));
	normal.y = 1;
	return (normal);
}

static t_vector				cylindreNormal(t_vector point, t_object obj)
{
	t_vector				normal;
	double					denominator;

	denominator = sqrt(pow(point.x, 2) + pow(point.z, 2));
	normal.x = obj.radius * (point.x / denominator);
	normal.z = obj.radius * (point.z / denominator);
	return (ft_normalize(normal));
}

static t_vector				coneNormal(t_vector point, t_object obj)
{
	t_vector				normal;
	double					neg;
	double					cosAngle;

	neg = point.y < 0 ? 1 : -1;
	cosAngle = cos(obj.angle);
	normal.x = point.x * cosAngle;
	normal.z = point.z * cosAngle;
	normal.y = sin(obj.angle) * neg;
	return (ft_normalize(normal));
}

t_vector					normal(t_vector point, t_object obj)
{
	t_vector				(*func[NBR_SHAPE])(t_vector, t_object) = {
		sphereNormal, planNormal, cylindreNormal, coneNormal};
	
	return (ft_normalize(func[obj.type](point, obj)));
}
