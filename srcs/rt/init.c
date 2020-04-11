#include "rt.h"
//#include "mlx.h"
#include <math.h>
#include <stdlib.h>

/*void				rt_delenv(t_env *env)
{
	mlx_destroy_image(env->mlx.mlx, env->mlx.image);
	if (env->form)
		ft_memdel((void**)&env->form);
	if (env->lum)
		ft_memdel((void**)&env->lum);
	exit(1);
}

static void			rt_initmlx(t_env *env)
{
	env->mlx.mlx = mlx_init();
	env->mlx.image = mlx_new_image(env->mlx.mlx, SCREENX, SCREENY);
	env->mlx.id = mlx_new_window(env->mlx.mlx, SCREENX, SCREENX, "RayTracer de Robin");
	env->mlx.mem_image = (unsigned int*)mlx_get_data_addr(env->mlx.image,
			&env->mlx.pix, &env->mlx.size_line, &env->mlx.endian);
}

void				rt_addPixel(t_mlx *mlx, t_vector color, int pos)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;

	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	mlx->mem_image[pos] = color_rgb;
}

t_vector			rt_attribute_color(int color)
{
	t_vector		vcolor;
	
	vcolor.x = (double)(color >> 16 & 0xFF) / 255;
	vcolor.y = (double)(color >> 8 & 0xFF) / 255;
	vcolor.z = (double)(color & 0xFF) / 255;
	return (vcolor);
}

int				rt_manager(void *param)
{
	int			pos;
	t_vector		color;
	t_mlx			*mlx;

	mlx = (t_mlx*)param;
	pos = 0;
	color.x = 0xFF;
	color.y = 0x00;
	color.z = 0x00;
	while (pos < PIXELS)
	{
		rt_addPixel(mlx, color, pos);
		pos++; 
	}
	mlx_put_image_to_window(mlx->mlx, mlx->id, mlx->image, 0, 0);
	return (0);
}

int				rt_main(t_env *env)
{
//	rt_initmlx(env);
	//mlx_hook(mlx.id, KEYPRESS, 0, rt_keypress, void);
	//mlx_hook(mlx.id, REDBUTTON, 0, void, void);
	//mlx_hook(mlx.id, MOUSEPRESS, 0, void, void);
	//mlx_hook(mlx.id, KEYRELEASE, 0, void, void);
//	mlx_loop_hook(env->mlx.mlx, rt_manager, &env->mlx);
//	mlx_loop(env->mlx.mlx);
	return (1);
}*/
