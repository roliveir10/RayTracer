#include "rt.h"

int			initLib(t_lib *lib)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (0);
	if (!(lib->window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, g_env.scene.work_dims.x, g_env.scene.work_dims.y, 0)))
		return (0);
	if (!(lib->renderer = SDL_CreateRenderer(lib->window, -1,
			SDL_RENDERER_PRESENTVSYNC)))
		return (0);
	if (!(lib->texture = SDL_CreateTexture(lib->renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
			g_env.scene.work_dims.x, g_env.scene.work_dims.y)))
		return (0);
	return (1);
}

