#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include "lexer.h"
# include "data.h"

# define NBR_KEY 1
# define NBR_MKEY 2
# define NBR_ELEMENT 4
# define NBR_THREAD 6

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

typedef enum			e_mkey
{
	MDOWN = 4,
	MUP
}						t_mkey;

typedef enum			e_color
{
	WHITE = 0xffffff,
	GREEN = 0x00ff00
}						t_color;

typedef struct			s_mlx
{
	void				*mlx;
	void				*image[2];
	void				*id;
	unsigned int		*mem_image[2];
	int					pix[2];
	int					size_line[2];
	int					endian[2];
	int					loadX;
	int					loadY;
}						t_mlx;

typedef enum			s_image
{
	RT,
	LOAD
}						t_image;

typedef struct			s_env
{
	t_mlx				mlx;
	int					resolution;
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
int						printWindow(void);
char					*open_file(char *argv);
int						fillStruct(t_ast *ast);

int						keyPress(int keycode);
int						mousePress(int keycode, int x, int y);
int						rt_close(void);

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
void					moveCamZ(int keycode);

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

void					printLoading(t_mlx *mlx, t_scene scene, int y);

// UI

void					addRectImage(unsigned int **image, int startX, int startY, int sizeX, int sizeY, int color);
void					printImage(t_mlx *mlx, int imageId, int x, int y);
// FREE

void					delenv(void);
void					freeStruct(void);
#endif
