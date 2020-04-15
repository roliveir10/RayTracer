#include <stdlib.h>
#include <math.h>
#include "rt.h"

void					addPixel(t_mlx mlx, t_vector color, int x, int y)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;
	int					offSetX;
	int					offSetY;

	offSetX = x + PIXPERUNIT;
	offSetY = y + PIXPERUNIT;
	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	for (int i = y; i < offSetY; i++)
		for (int j = x; j < offSetX; j++)
		{
			if (j + i * SCREENX < RESOLUTION)
				mlx.mem_image[j + i * SCREENX] = color_rgb;
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
	hit = rayCast(g_env.camera.origin, rayDir, MAX_DIST_TO_PRINT);
	if (hit.distance > 0)
		hit.color = light(hit);
	return (hit.color);
}

int						printWindow(void)
{
	t_vector			color;

	for (int i = 0; i < SCREENY; i += PIXPERUNIT)
		for (int j = 0; j < SCREENX; j += PIXPERUNIT)
		{
			ft_bzero(&color, sizeof(t_vector));
			for (int s = 0; s < SAMPLE_RATE; s++)
				color = ft_vadd(color, pixColor(i, j));
			color = ft_vdiv(color, SAMPLE_RATE);
			addPixel(g_env.mlx, color, j, i);
		}
	mlx_put_image_to_window(g_env.mlx.mlx, g_env.mlx.id, g_env.mlx.image, 0, 0);
	return (1);
}
