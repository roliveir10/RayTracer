#include <stdlib.h>
#include "rt.h"

void				delenv(t_lib *lib)
{
	if (lib->renderer)
		SDL_DestroyRenderer(lib->renderer);
	if (lib->window)
		SDL_DestroyWindow(lib->window);
	SDL_Quit();
	freeStruct();
	exit(1);
}

static int		initLib(t_lib *lib)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (0);
	if (!(lib->window = SDL_CreateWindow(WIN_TITLE, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, g_env.scene.screenX, g_env.scene.screenY, 0)))
		return (0);
	if (!(lib->renderer = SDL_CreateRenderer(lib->window, -1,
			SDL_RENDERER_PRESENTVSYNC)))
		return (0);
	if (!(lib->texture = SDL_CreateTexture(lib->renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
			g_env.scene.screenX, g_env.scene.screenY)))
		return (0);
	return (1);
}

int				rt_main(void)
{
	if (!initLib(&g_env.lib))
		return (0);
	if (!initLoadBar(&g_env.lib))
		return (0);
	g_env.resolution = g_env.scene.screenX * g_env.scene.screenY;
	initCamera(&(g_env.camera));
	initializeRotation();
	runLoop();
	delenv(&g_env.lib);
	return (1);
}
