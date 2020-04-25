#include "rt.h"

static void			printTexture(void)
{
	int				pitch;

	if (!SDL_LockTexture(g_env.lib.texture, NULL, (void**)&g_env.lib.image, &pitch))
	{
		printWindow();
		SDL_UnlockTexture(g_env.lib.texture);
		SDL_RenderCopy(g_env.lib.renderer, g_env.lib.texture, NULL, NULL);
		SDL_RenderPresent(g_env.lib.renderer);
	}
}

static void			rayLoop(void)
{	
	if (g_env.scene.pixPerUnit > 0)
	{
		drawBar(&g_env.lib, 0, 0);
		printTexture();
	}
	g_env.scene.pixPerUnit = 0;
}

void				runLoop(void)
{
	SDL_Event		event;

	g_env.running = 1;
	while (g_env.running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT
				|| (event.type == SDL_KEYDOWN
					&& event.key.keysym.sym == SDLK_ESCAPE)
				|| (event.type == SDL_WINDOWEVENT
					&& event.window.event == SDL_WINDOWEVENT_CLOSE))
			{
				g_env.running = 0;
				break ;
			}
			keyHandler(&event);
		}
		if (g_env.running == 1)
			rayLoop();
	}
}
