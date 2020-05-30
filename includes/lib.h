#ifndef LIB_H
# define LIB_H

# include "rt.h"
# include "SDL.h"

# define WIN_TITLE "RayTracer de Robin"

typedef struct s_scene	t_scene;

typedef struct			s_load
{
	SDL_Texture			*texture;
	unsigned int		*image;
	SDL_Rect			loadRect;
}						t_load;

typedef struct			s_lib
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*display;
	t_load				load;
}						t_lib;

// LIB

int						initLib(t_lib *lib);

// FREE

void					delenv(t_lib *lib);

// LOADING

int						initLoadBar(t_lib *lib);
void					drawBar(t_lib *lib, int currentLoad, int loading);

#endif
