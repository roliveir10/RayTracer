#include <stdlib.h>
#include <math.h>
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
				mlx.mem_image[j + i * g_env.scene.screenX] = color_rgb;
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

static void				printLoading(int y)
{
	double				percent;

	percent = (double)y / g_env.scene.screenY * 100;
	printf("Loading: %d%%\n", (int)percent);
}

int						printWindow(void)
{
	t_vector			color;


	for (int i = 0; i < g_env.scene.screenY; i += g_env.scene.pixPerUnit)
	{
		for (int j = 0; j < g_env.scene.screenX; j += g_env.scene.pixPerUnit)
		{
			ft_bzero(&color, sizeof(t_vector));
			for (int s = 0; s < g_env.scene.sampleRate; s++)
				color = ft_vadd(color, pixColor(i, j));
			color = ft_vdiv(color, g_env.scene.sampleRate);
			addPixel(g_env.mlx, color, j, i);
		}
		if (i % (g_env.scene.screenY / 20) == 0)
			printLoading(i);
	}
	mlx_put_image_to_window(g_env.mlx.mlx, g_env.mlx.id, g_env.mlx.image, 0, 0);
	return (1);
}
