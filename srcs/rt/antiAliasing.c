#include "rt.h"

static t_vector			pixColor(int i, int j)
{
	t_vector			rayDir;
	t_rayHit			hit;
	double				x;
	double				y;

	y = (double)i + drand48();
	x = (double)j + drand48();
	rayDir = vDirCamToPoint(g_env.camera, x, y);
	hit = rayCast(g_env.camera.origin, rayDir, g_env.scene.maxDistToPrint);
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
