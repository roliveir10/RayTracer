#include "rt.h"

static void		drawBgBar(t_lib *lib)
{
	for (int i = 0; i < lib->load.loadRect.h; i++)
		for (int j = 0; j < lib->load.loadRect.w; j++)
			lib->load.image[i * lib->load.loadRect.w + j] = WHITE;
}

static void		drawLoadingBar(t_lib *lib, int currentLoad)
{
	int			width;

	width = lib->load.loadRect.w * 0.01 * 8; // can be optimize
	for (int i = 0; i < lib->load.loadRect.h; i++)
		for (int j = currentLoad - width; j < currentLoad + width; j++)
		{
			if (j >= 0 && j < lib->load.loadRect.w)
				lib->load.image[i * lib->load.loadRect.w + j] = GREEN;
		}
}

void			drawBar(t_lib *lib, int currentLoad, int loading)
{
	int			p;

	if (!SDL_LockTexture(lib->load.texture, NULL, (void**)&lib->load.image, &p))
	{
		SDL_RenderClear(lib->renderer);
		if (loading)
			drawLoadingBar(lib, currentLoad);
		else
			drawBgBar(lib);
		SDL_UnlockTexture(lib->load.texture);
		SDL_RenderCopy(lib->renderer, lib->load.texture, NULL, &lib->load.loadRect);
		SDL_RenderPresent(lib->renderer);
	}
}

int				initLoadBar(t_lib *lib)
{
	lib->load.loadRect.w = g_env.scene.work_dims.x * 0.25;
	lib->load.loadRect.h = g_env.scene.work_dims.y * 0.05;
	lib->load.loadRect.x = (g_env.scene.work_dims.x - lib->load.loadRect.w) * 0.5;
	lib->load.loadRect.y = g_env.scene.work_dims.y * 0.9;
	if (!(lib->load.texture = SDL_CreateTexture(lib->renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
			lib->load.loadRect.w, lib->load.loadRect.h)))
		return (0);
	return (1);
}
