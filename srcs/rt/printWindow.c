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

static void				*printLine(void *arg)
{
	int					incy;
	int					starty;
	t_vector			color;

	incy = g_env.scene.pixPerUnit * NBR_THREAD;
	starty = g_env.scene.pixPerUnit * (intptr_t)arg;
	for (int y = starty; y < g_env.scene.screenY; y += incy)
	{
		for (int x = 0; x < g_env.scene.screenX; x += g_env.scene.pixPerUnit)
		{
			color = antiAliasing(g_env.scene.sampleRate, x, y);
			addPixel(color, x, y);
		}
		if (y % (g_env.scene.screenY / 100) == 0)
			drawBar(&g_env.lib, (double)y / g_env.scene.screenY * g_env.lib.load.loadRect.w, 1);
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
