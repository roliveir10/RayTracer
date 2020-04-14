#include "rt.h"
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

int				rt_main(void)
{
	initmlx();
	initCamera(&(g_env.camera));
	initializeRotation();
	mlx_hook(g_env.mlx.id, KEYPRESS, 0, keyPress, NULL);
	mlx_hook(g_env.mlx.id, REDBUTTON, 0, rt_close, NULL);
	mlx_hook(g_env.mlx.id, MOUSEPRESS, 0, mousePress, NULL);
//	mlx_hook(g_env.mlx.id, KEYRELEASE, 0, void, void);
	printWindow();
//	mlx_loop_hook(g_env.mlx.mlx, rt_manager, &g_env.mlx);
	mlx_loop(g_env.mlx.mlx);
	return (1);
}
