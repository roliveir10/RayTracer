#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include "lib.h"
# include "libft.h"
# include "lexer.h"
# include "data.h"

# define NBR_KEY 1
# define NBR_MKEY 2
# define NBR_ELEMENT 4
# define NBR_THREAD 6

typedef enum			e_color
{
	WHITE = 0xffffff,
	GREEN = 0x00ff00
}						t_color;

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
	t_vector			viewDir;
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
t_vector				hitPoint(t_vector o, t_vector dir, double dist);
double					limit(t_vector o, t_vector dir, double dist, t_object obj);

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
t_vector				ambient(t_light light);
t_vector				diffuse(t_light light, double angle, t_vector intensity);
t_vector				specular(t_light light, t_rayHit hit, t_vector reflectDir, t_vector intensity);

// COLOR

t_vector				setColor(int color);

// ANTIALIASING

t_vector				antiAliasing(int sampleRate, int x, int y);

// FREE
void					freeStruct(void);
#endif
