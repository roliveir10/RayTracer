#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "rt.h"

static void				addPixel(t_vector color, int x, int y)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;
	int					pos;

	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	for (int i = 0; i < g_env.scene.pixPerUnit; i++)
		for (int j = 0; j < g_env.scene.pixPerUnit; j++)
		{
			if ((pos = (y + i) * g_env.scene.screenX + (x + j)) < g_env.resolution)
				g_env.lib.image[pos] = color_rgb;
		}
}

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

static void				*printLine(void *arg)
{
	t_vector			color;
	int					incy;

	incy = g_env.scene.pixPerUnit * NBR_THREAD;
	for (int y = g_env.scene.pixPerUnit * (intptr_t)arg; y < g_env.scene.screenY; y += incy)
	{
		for (int x = 0; x < g_env.scene.screenX; x += g_env.scene.pixPerUnit)
		{
			ft_bzero(&color, sizeof(t_vector));
			for (int s = 0; s < g_env.scene.sampleRate; s++)
				color = ft_vadd(color, pixColor((intptr_t)arg, x));
			color = ft_vdiv(color, g_env.scene.sampleRate);
			addPixel(color, x, y);
		}
		if (y % (g_env.scene.screenY / 100) == 0)
			printf("Loading: %d%%\n", (int)((double)y / g_env.scene.screenY * 100));
			//	printLoading(&g_env.mlx, g_env.scene, (intptr_t)arg);
		}
	}
	return (NULL);
}

void					printWindow(void)
{
	pthread_t			id[NBR_THREAD];

	for (int i = 0; i < NBR_THREAD; i++)
		pthread_create(&id[i], NULL, printLine, (void*)(intptr_t)i);
	for (int i = 0; i < NBR_THREAD; i++)
		pthread_join(id[i], NULL);
}
