#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include "libft.h"
# include "lexer.h"
# include "data.h"
# include "SDL.h"

# define NBR_KEY 1
# define NBR_MKEY 2
# define NBR_ELEMENT 4
# define NBR_THREAD 6
# define WIN_TITLE "RayTracer de Robin"

typedef enum			e_color
{
	WHITE = 0xffffff,
	GREEN = 0x00ff00
}						t_color;

typedef struct			s_lib
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	unsigned int		*image;
	int					loadX;
	int					loadY;
}						t_lib;

typedef enum			s_image
{
	RT,
	LOAD
}						t_image;

typedef struct			s_env
{
	t_lib				lib;
	t_scene				scene;
	t_camera			camera;
	t_light				*light;
	t_object			*object;
	int					running;
	int					resolution;
}						t_env;

typedef struct			s_rayHit
{
	double				distance;
	t_vector			normal;
	t_vector			point;
	t_vector			color;
	t_object			obj;
}						t_rayHit;

t_env					g_env;

int						rt_main(void);
void					runLoop();
void					printWindow(void);
char					*open_file(char *argv);
int						fillStruct(t_ast *ast);

// LIBHOOK

void					runLoop(void);
void					keyHandler(SDL_Event *event);
// SHAPEINTER

double					plan(t_object obj, t_vector o, t_vector dir);
double					sphere(t_object obj, t_vector o, t_vector dir);
double					cylindre(t_object obj, t_vector o, t_vector dir);
double					cone(t_object obj, t_vector o, t_vector dir);

//RAYCAST

t_rayHit				rayCast(t_vector o, t_vector dir, double maxDist);
double					distToHit(t_object obj, t_vector o, t_vector dir);

//VECTOR

t_vector				vDirCamToPoint(t_camera cam, double x, double y);

//CAMERA

void					initCamera(t_camera *cam);

// ROTATION

void					initializeRotation(void);
void					changeReference(t_vector *o, t_vector *dir, t_object obj);
t_vector				changePointReference(t_vector point, t_object obj);
t_vector				resetPointReference(t_object obj, t_vector point);

// NORMAL

t_vector				normal(t_vector point, t_object obj);

// LIGHT

t_vector				light(t_rayHit hit);

// COLOR

t_vector				setColor(int color);

// LOADING

//void					printLoading(t_mlx *mlx, t_scene scene, int y);

// UI

//void					addRectImage(unsigned int **image, int startX, int startY, int sizeX, int sizeY, int color);
//void					printImage(t_mlx *mlx, int imageId, int x, int y);
// FREE

void					delenv(t_lib *lib);
void					freeStruct(void);
#endif
