#include <math.h>
#include "rt.h"

t_vector				ambient(t_light light)
{
	return (ft_vmul(light.color, g_env.scene.ambient));
}

t_vector				diffuse(t_light light, double angle)
{
	return (ft_vmul(light.color, angle));
}

t_vector				specular(t_light light, t_rayHit hit, t_vector reflectDir)
{
	double				spec;

	spec = pow(ft_max(ft_dot(hit.viewDir, reflectDir), 0), hit.obj.shininess);
	return (ft_vmul(light.color, spec * hit.obj.shininessStrength));
}
