#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "lexer.h"
# include "data.h"

# define SCREENX 900
# define SCREENY 900
# define PIXELS SCREENX * SCREENY
# define FOV 1000

# define NBR_KEY 1
# define NBR_ELEMENT 4

typedef enum			e_event
{
	KEYPRESS = 2,
	REDBUTTON = 17,
	MOUSEPRESS = 4,
	KEYRELEASE = 3
}						t_event;

typedef enum			e_key
{
	KESCAP = 53,
	KLEFT,
	KRIGHT,
	KUP,
	KDOWN
}						t_key;

typedef struct			s_mlx
{
	void				*mlx;
	void				*image;
	void				*id;
	unsigned int		*mem_image;
	int					pix;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct			s_env
{
	t_mlx				mlx;
	t_scene				scene;
	t_camera			camera;
	t_light				*light;
	t_object			*object;
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
char					*open_file(char *argv);
int						fillStruct(t_ast *ast);

int						keyPress(int keycode);
int						rt_close(void);

// SHAPEINTER

double					plan(t_object obj, t_vector o, t_vector dir);
double					sphere(t_object obj, t_vector o, t_vector dir);
double					cylindre(t_object obj, t_vector o, t_vector dir);
double					cone(t_object obj, t_vector o, t_vector dir);

//RAYCAST

t_rayHit				rayCast(t_vector o, t_vector dir, double maxDist);

//VECTOR

t_vector				vDirCamToPoint(t_camera cam, double x, double y);

//CAMERA

void					initCamera(t_camera *cam);

// ROTATION

void					initializeRotation(void);
void					changeReference(t_vector *o, t_vector *dir, t_object obj);
t_vector				resetPointReference(t_object obj, t_vector point);

// NORMAL

t_vector				normal(t_vector point, t_object obj);

// FREE

void					delenv(void);
void					freeStruct(void);
#endif
