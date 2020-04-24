#include "rt.h"

static t_vector			reflect(t_vector I, t_vector N)
{
	return (ft_vsub(ft_vmul(N, ft_dot(N, I) * 2.0), I));
}

static t_vector			lightDir(t_vector o, t_light light)
{
	if (light.etype == POINTL)
		return (ft_get_vector(o, light.origin));
	return (light.origin);
}

static t_vector			lightIntensity(t_light light, t_vector hitPoint)
{
	double				dist;
	t_vector			intensity;

	intensity.x = 1.0;
	intensity.y = 1.0;
	intensity.z = 1.0;
	if (light.etype == POINTL)
	{
		dist = ft_vdist(light.origin, hitPoint);
		intensity = ft_vmul(light.color, light.intensity / (12.556 * pow(dist, 2)));
	}
	return (intensity);
}

static int				hitLight(t_ray ray, t_object obj, t_light light)
{
	double				distance;

	distance = distToHit(obj, ray);
	if (distance > 0)
	{
		if (light.etype == DIRECTIONAL)
			return (0);
		if (distance < ft_vdist(light.origin, ray.o))
			return (0);
	}
	return (1);
}

static t_vector			getLightAt(t_object *obj, t_light light, t_rayHit hit, t_vector lDir)
{
	double				angle;
	t_vector			color;
	t_vector			reflectDir;
	t_vector			intensity;

	ft_bzero(&color, sizeof(t_vector));
	if (obj)
		return (ft_vvmul(ambient(light), hit.obj.color));
	angle = ft_max(ft_dot(hit.normal, lDir), 0);
	reflectDir = reflect(ft_vmul(lDir, -1), hit.normal);
	intensity = lightIntensity(light, hit.point);
	color = ft_vadd(ambient(light), diffuse(light, angle, intensity));
	color = ft_vvmul(color, hit.obj.color);
	return (ft_vadd(color, specular(light, hit, reflectDir, intensity)));
}

//vDir : light to point

t_vector				light(t_rayHit hit)
{
	t_vector			color;
	t_object			*currentObj;
	t_light				*currentLight;
	t_ray				ray;

	currentLight = g_env.light;
	ft_bzero(&color, sizeof(t_vector));
	while (currentLight)
	{
		currentObj = g_env.object;
		fillRay(hit.point, lightDir(hit.point, *currentLight), &ray);
		while (currentObj)
		{
			if (!hitLight(ray, *currentObj, *currentLight))
				break ;
			currentObj = currentObj->next;
		}
		color = ft_vadd(color, getLightAt(currentObj, *currentLight, hit, ray.dir));
		currentLight = currentLight->next;
	}
	return (color);
}
