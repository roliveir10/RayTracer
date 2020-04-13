#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "lexer.h"
# include "data.h"

# define SCREENX 1440
# define SCREENY 900
# define PIXELS SCREENX * SCREENY
# define FOV 10
# define VIEW_PLANE_WIDTH SCREENX / 100
# define VIEW_PLANE_HEIGHT SCREENY / 100

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
}						t_rayHit;

t_env					g_env;

int						rt_main(void);
char					*open_file(char *argv);
int						fillStruct(t_ast *ast);

int						keyPress(int keycode);
int						rt_close(void);

//RAYCAST

t_rayHit				rayCast(t_vector o, t_vector dir, double maxDist);

//VECTOR

t_vector				vDirCamToPoint(t_camera cam, double x, double y);

//CAMERA

void					initCamera(t_camera *cam);

// FREE

void					delenv(void);
void					freeStruct(void);
#endif
