#include "rt.h"

static int				hitLight(t_vector o, t_vector dir, t_object obj, t_light light)
{
	double				distance;

	distance = distToHit(obj, o, dir);
	if (distance > 0)
	{
		if (distance < ft_vdist(light.origin, o))
			return (0);
	}
	return (1);
}

static t_vector			ambientOnly(void)
{
	t_vector			color;

	ft_bzero(&color, sizeof(t_vector));
	return (color);
}

static t_vector			getLightAt(t_object *obj, t_light light, t_rayHit hit)
{
	t_vector			lDir;
	double				angle;
	t_vector			color;

	if (obj)
		return (ambientOnly());
	lDir = ft_get_vector(hit.point, light.origin);
	angle = ft_dot(hit.normal, lDir);
	if (angle > 0)
	{
		color = ft_vvmul(hit.obj.color, light.color);
		return (ft_vmul(color, angle));
	}
	return (ambientOnly());
}

t_vector				light(t_rayHit hit)
{
	t_vector			color;
	t_object			*currentObj;
	t_light				*currentLight;
	t_vector			vDir;

	currentLight = g_env.light;
	ft_bzero(&color, sizeof(t_vector));
	while (currentLight)
	{
		currentObj = g_env.object;
		vDir = ft_get_vector(hit.point, currentLight->origin);
		while (currentObj)
		{
			if (!hitLight(hit.point, vDir, *currentObj, *currentLight))
				break ;
			currentObj = currentObj->next;
		}
		color = ft_vadd(color, getLightAt(currentObj, *currentLight, hit));
		currentLight = currentLight->next;
	}
	return (color);
}
