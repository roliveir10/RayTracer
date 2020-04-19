#include <math.h>
#include "rt.h"

t_vector				ambient(t_light light)
{
	return (ft_vmul(light.color, g_env.scene.ambient));
}

t_vector				diffuse(t_light light, double angle, t_vector intensity)
{
	t_vector			diffuse;

	diffuse = ft_vmul(light.color, angle);
	diffuse = ft_vvmul(diffuse, intensity);
	diffuse = ft_vdiv(diffuse, M_PI);
	return (diffuse);
}

t_vector				specular(t_light light, t_rayHit hit, t_vector reflectDir, t_vector intensity)
{
	double				spec;
	t_vector			specular;

	spec = pow(ft_max(ft_dot(hit.viewDir, reflectDir), 0), hit.obj.shininess);
	specular = ft_vmul(intensity, spec * hit.obj.shininessStrength);
	return ft_vvmul(light.color, specular);
}
