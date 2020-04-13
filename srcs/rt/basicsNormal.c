#include <math.h>
#include "rt.h"

static t_vector				sphereNormal(t_vector point, t_object obj)
{
	(void)obj;
	return (point);
}

static t_vector				planNormal(t_vector point, t_object obj)
{
	(void)obj;
	return (point);
}

static t_vector				cylindreNormal(t_vector point, t_object obj)
{
	(void)obj;
	return (point);
}

static t_vector				coneNormal(t_vector point, t_object obj)
{
	(void)obj;
	return (point);
}

t_vector					normal(t_vector point, t_object obj)
{
	t_vector				(*func[NBR_SHAPE])(t_vector, t_object) = {
		sphereNormal, planNormal, cylindreNormal, coneNormal};
	
	return (ft_normalize(func[obj.type](point, obj)));
}
