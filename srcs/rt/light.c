#include "rt.h"

static t_vector			reflect(t_vector I, t_vector N)
{
	return (ft_vsub(ft_vmul(N, ft_dot(N, I) * 2.0), I));
}

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

static t_vector			getLightAt(t_object *obj, t_light light, t_rayHit hit, t_vector lDir)
{
	double				angle;
	t_vector			color;
	t_vector			reflectDir;

	ft_bzero(&color, sizeof(t_vector));
	if (obj)
		return (ft_vvmul(ambient(light), hit.obj.color));
	angle = ft_max(ft_dot(hit.normal, lDir), 0);
	reflectDir = reflect(ft_vmul(lDir, -1), hit.normal);
	color = ft_vadd(ambient(light), diffuse(light, angle));
	color = ft_vvmul(color, hit.obj.color);
	return (ft_vadd(color, specular(light, hit, reflectDir)));
	//color = ft_vvmul(hit.obj.color, light.color);
	//return (ft_vadd(ft_vmul(color, angle), ambientOnly(light, hit.obj)));
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
		color = ft_vadd(color, getLightAt(currentObj, *currentLight, hit, vDir));
		currentLight = currentLight->next;
	}
	return (color);
}
