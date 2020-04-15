#include "rt.h"

void				changeReference(t_vector *o, t_vector *dir, t_object obj)
{
	*o = ft_vsub(obj.origin, *o);
	for (int i = 0; i < 3; i++)
	{
		*dir = ft_vrotate(*dir, obj.matRot[i]);
		*o = ft_vrotate(*o, obj.matRot[i]);
	}
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
	ft_fmat(&cmat, g_env.camera.rotation, -1);
	for (i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			g_env.camera.direction[i] = ft_vrotate(g_env.camera.direction[i], cmat[j]);
	lightTmp = g_env.light;
	while (g_env.light)
	{
		g_env.light->direction = ft_normalize(g_env.light->direction);
		g_env.light = g_env.light->next;
	}
	g_env.light = lightTmp;
}
