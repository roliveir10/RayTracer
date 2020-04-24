#include "rt.h"

void				fillRay(t_vector o, t_vector dir, t_ray *ray)
{
	ray->o = o;
	ray->dir = dir;
	ray->invDir = ft_divv(1.0, dir);
	ray->sign[0] = (ray->invDir.x < 0);
	ray->sign[1] = (ray->invDir.y < 0);
	ray->sign[2] = (ray->invDir.z < 0);
}

static t_vector			pixColor(int i, int j)
{
	t_ray				ray;
	t_rayHit			hit;
	double				x;
	double				y;

	y = (double)i + drand48();
	x = (double)j + drand48();
	fillRay(g_env.camera.origin, vDirCamToPoint(g_env.camera, x, y), &ray);
	hit = rayCast(ray, g_env.scene.maxDistToPrint);
	if (hit.distance > 0)
		hit.color = light(hit);
	return (hit.color);
}

t_vector				antiAliasing(int sampleRate, int x, int y)
{
	t_vector			color;

	ft_bzero(&color, sizeof(t_vector));
	for (int s = 0; s < sampleRate; s++)
		color = ft_vadd(color, pixColor(y, x));
	color = ft_vdiv(color, sampleRate);
	return (color);
}
