#include "rt.h"

void				changeReference(t_ray *ray, t_object obj)
{
	ray->o = ft_vsub(obj.origin, ray->o);
	for (int i = 0; i < 3; i++)
	{
		ray->dir = ft_vrotate(ray->dir, obj.matRot[i]);
		ray->o = ft_vrotate(ray->o, obj.matRot[i]);
	}
	if (obj.type == BOX)
		fillRay(ray->o, ray->dir, ray);
}

t_vector				changePointReference(t_vector point, t_object obj)
{
	point = ft_vsub(obj.origin, point);
	for (int i = 0; i < 3; i++)
		point = ft_vrotate(point, obj.matRot[i]);
	return (point);
}

t_vector				resetPointReference(t_object obj, t_vector point)
{
	t_vector			new;

	new = point;
	for (int i = 2; i >= 0; i--)
		new = ft_vrotate(new, obj.matRotInv[i]);
	new = ft_vadd(new, obj.origin);
	return (new);
}

void				initializeRotation(void)
{
	double			cmat[3][3][3];
	int				i;
	t_object		*objTmp;
	t_light			*lightTmp;

	objTmp = g_env.object;
	while (g_env.object)
	{
		ft_fmat(&g_env.object->matRot, g_env.object->rotation, -1);
		ft_fmat(&g_env.object->matRotInv, g_env.object->rotation, 1);
		g_env.object = g_env.object->next;
	}
	g_env.object = objTmp;
	g_env.camera.direction[0].x = 1.0;
	g_env.camera.direction[1].y = 1.0;
	g_env.camera.direction[2].z = 1.0;
	ft_fmat(&cmat, g_env.camera.rotation, -1);
	for (i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			g_env.camera.direction[i] = ft_vrotate(g_env.camera.direction[i], cmat[j]);
	lightTmp = g_env.light;
	while (g_env.light)
	{
		if (g_env.light->etype == DIRECTIONAL)
			g_env.light->origin = ft_vmul(ft_normalize(g_env.light->origin), -1);
		g_env.light = g_env.light->next;
	}
	g_env.light = lightTmp;
}
