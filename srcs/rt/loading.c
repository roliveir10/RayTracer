#include "rt.h"

void					printLoading(t_mlx *mlx, t_scene scene, int index)
{
	double				percent;
	int					currentLoad;

	percent = (double)index / scene.screenY * 100;
	currentLoad = (int)percent * mlx->loadX * 0.01;
	addRectImage(&mlx->mem_image[1], currentLoad - mlx->loadX * 0.01, 0, currentLoad + mlx->loadX * 0.01, mlx->loadY, GREEN);
	printImage(mlx, 1, (scene.screenX - mlx->loadX) * 0.5, scene.screenY * 0.9);
	return ;
}
