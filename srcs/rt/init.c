#include "rt.h"
#include <stdlib.h>

void				delenv(void)
{
	mlx_destroy_image(g_env.mlx.mlx, g_env.mlx.image[0]);
	mlx_destroy_image(g_env.mlx.mlx, g_env.mlx.image[1]);
	freeStruct();
	exit(1);
}

static void			initmlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->loadX = g_env.scene.screenX * 0.5;
	mlx->loadY = g_env.scene.screenY * 0.05;
	mlx->image[0] = mlx_new_image(mlx->mlx, g_env.scene.screenX, g_env.scene.screenY);
	mlx->image[1] = mlx_new_image(mlx->mlx, mlx->loadX, mlx->loadY);
	mlx->id = mlx_new_window(mlx->mlx, g_env.scene.screenX, g_env.scene.screenY, "RayTracer de Robin");
	mlx->mem_image[0] = (unsigned int*)mlx_get_data_addr(mlx->image[0],
			&mlx->pix[0], &mlx->size_line[0], &mlx->endian[0]);
	mlx->mem_image[1] = (unsigned int*)mlx_get_data_addr(mlx->image[1],
			&mlx->pix[1], &mlx->size_line[1], &mlx->endian[1]);
	addRectImage(&mlx->mem_image[1], 0, 0, mlx->loadX, mlx->loadY, WHITE);
}

int				rt_main(void)
{
	initmlx(&g_env.mlx);
	g_env.resolution = g_env.scene.screenX * g_env.scene.screenY;
	initCamera(&(g_env.camera));
	initializeRotation();
	mlx_hook(g_env.mlx.id, KEYPRESS, 0, keyPress, NULL);
	mlx_hook(g_env.mlx.id, REDBUTTON, 0, rt_close, NULL);
	mlx_hook(g_env.mlx.id, MOUSEPRESS, 0, mousePress, NULL);
//	mlx_hook(g_env.mlx.id, KEYRELEASE, 0, void, void);
//	mlx_put_image_to_window(g_env.mlx.mlx, g_env.mlx.id, g_env.mlx.image[1],
//		g_env.scene.screenX * 0.5 - 50, g_env.scene.screenY * 0.5 - 10);
//	printWindow();
	mlx_loop_hook(g_env.mlx.mlx, printWindow, NULL);
	mlx_loop(g_env.mlx.mlx);
	return (1);
}
