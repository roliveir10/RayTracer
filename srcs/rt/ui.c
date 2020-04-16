#include "rt.h"

void			addRectImage(unsigned int **image, int startX, int startY, int sizeX, int sizeY, int color)
{
	for (int i = startY; i < sizeY; i++)
		for (int j = startX; j < sizeX; j++)
		{
			if (j < 0)
				break ;
			(*image)[i * g_env.mlx.loadX + j] = color;
		}
}

void			printImage(t_mlx *mlx, int imageId, int x, int y)
{
	mlx_put_image_to_window(mlx->mlx, mlx->id, mlx->image[imageId], x, y);
}
