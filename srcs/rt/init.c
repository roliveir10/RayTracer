#include "rt.h"

void				delenv(t_lib *lib)
{
	delOpenCL(&g_env.ocl);
	if (lib->renderer)
		SDL_DestroyRenderer(lib->renderer);
	if (lib->window)
		SDL_DestroyWindow(lib->window);
	SDL_Quit();
	exit(1);
}

int				rt_main(void)
{
	debugPrintFile();
	if (!initLib(&g_env.lib))
		return (0);
	if (!initLoadBar(&g_env.lib))
	{
		delenv(&g_env.lib);
		return (0);
	}
	if (!initOpenCL(CL_PLATFORM_UNINITIALIZED))
	{
		delenv(&g_env.lib);
		return (0);
	}
	initCamera(&g_env.scene.camera);
	runLoop();
	delenv(&g_env.lib);
	return (1);
}
