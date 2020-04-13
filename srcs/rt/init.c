#include "rt.h"
#include <math.h>
#include <stdlib.h>

void				delenv(void)
{
	mlx_destroy_image(g_env.mlx.mlx, g_env.mlx.image);
	freeStruct();
	exit(1);
}

static void			initmlx(void)
{
	g_env.mlx.mlx = mlx_init();
	g_env.mlx.image = mlx_new_image(g_env.mlx.mlx, SCREENX, SCREENY);
	g_env.mlx.id = mlx_new_window(g_env.mlx.mlx, SCREENX, SCREENY, "RayTracer de Robin");
	g_env.mlx.mem_image = (unsigned int*)mlx_get_data_addr(g_env.mlx.image,
			&g_env.mlx.pix, &g_env.mlx.size_line, &g_env.mlx.endian);
}

void				addPixel(t_mlx *mlx, t_vector color, int pos)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;

	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	mlx->mem_image[pos] = color_rgb;
}

t_vector			attribute_color(int color)
{
	t_vector		vcolor;
	
	vcolor.x = (double)(color >> 16 & 0xFF) / 255;
	vcolor.y = (double)(color >> 8 & 0xFF) / 255;
	vcolor.z = (double)(color & 0xFF) / 255;
	return (vcolor);
}

int				rt_manager(void *param)
{
	int				pos;
	t_mlx			*mlx;
	t_rayHit		hit;

	mlx = (t_mlx*)param;
	pos = 0;
	while (pos < PIXELS)
	{
		hit = rayCast(g_env.camera.origin, vDirCamToPoint(g_env.camera, pos % SCREENX, pos / SCREENY), 100000);
		if (hit.distance > 0)
			addPixel(mlx, hit.color, pos);
		else
			addPixel(mlx, hit.color, pos);
		pos++; 
	}
	mlx_put_image_to_window(mlx->mlx, mlx->id, mlx->image, 0, 0);
	return (1);
}

int				rt_main(void)
{
	initmlx();
	initCamera(&(g_env.camera));
	initializeRotation();
	mlx_hook(g_env.mlx.id, KEYPRESS, 0, keyPress, NULL);
	mlx_hook(g_env.mlx.id, REDBUTTON, 0, rt_close, NULL);
//	mlx_hook(g_env.mlx.id, MOUSEPRESS, 0, void, void);
//	mlx_hook(g_env.mlx.id, KEYRELEASE, 0, void, void);
	mlx_loop_hook(g_env.mlx.mlx, rt_manager, &g_env.mlx);
	mlx_loop(g_env.mlx.mlx);
	return (1);
}
