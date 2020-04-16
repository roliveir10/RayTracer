#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "rt.h"

void					addPixel(t_mlx mlx, t_vector color, int x, int y)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;
	int					offSetX;
	int					offSetY;

	offSetX = x + g_env.scene.pixPerUnit;
	offSetY = y + g_env.scene.pixPerUnit;
	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	for (int i = y; i < offSetY; i++)
		for (int j = x; j < offSetX; j++)
		{
			if (j + i * g_env.scene.screenX < g_env.resolution)
				mlx.mem_image[0][j + i * g_env.scene.screenX] = color_rgb;
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

	for (int x = 0; x < g_env.scene.screenX; x += g_env.scene.pixPerUnit)
	{
		ft_bzero(&color, sizeof(t_vector));
		for (int s = 0; s < g_env.scene.sampleRate; s++)
			color = ft_vadd(color, pixColor((intptr_t)arg, x));
		color = ft_vdiv(color, g_env.scene.sampleRate);
		addPixel(g_env.mlx, color, x, (intptr_t)arg);
	}
	if ((intptr_t)arg % (g_env.scene.screenY / 100) == 0)
		printLoading(&g_env.mlx, g_env.scene, (intptr_t)arg);
	return (NULL);
}

static void				createThread(int y)
{
	pthread_t			id[NBR_THREAD];

	for (int i = 0; i < NBR_THREAD; i++)
		pthread_create(&id[i], NULL, printLine, (void*)(intptr_t)(y + i * g_env.scene.pixPerUnit));
	for (int i = 0; i < NBR_THREAD; i++)
		pthread_join(id[i], NULL);
}

int						printWindow(void)
{
	static int			i = 0;
	
	if (i < g_env.scene.screenY)
	{
		createThread(i);
		i += g_env.scene.pixPerUnit * NBR_THREAD;
	}
	if (i >= g_env.scene.screenY)
		mlx_put_image_to_window(g_env.mlx.mlx, g_env.mlx.id, g_env.mlx.image[0], 0, 0);
	return (1);
}
