#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include <math.h>
# include "lib.h"
# include "libft.h"
# include "lexer.h"
# include "data.h"
# include "cl.h"

# define NBR_KEY 1
# define NBR_MKEY 2
# define NBR_ELEMENT 4

# define EPS 0.00003

# define DEFAULT_BOUNCE 4
# define DEFAULT_MAX_DIST_TO_PRINT 15000
# define DEFAULT_SAMPLE_RATE 128
# define DEFAULT_SCREENX 1280
# define DEFAULT_SCREENY 800
# define DEFAULT_FOV 3 * M_PI / 180

# define SCREEN_MIN 100

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

typedef struct			s_sizet3
{
	size_t				x;
	size_t				y;
	size_t				z;
}						t_sizet3;

typedef struct			s_env
{
	t_lib				lib;
	t_cl				ocl;
	t_scene				scene;
	int					resolution;
	int					running;
	int					print;
}						t_env;

typedef struct			s_rayHit
{
	float				distance;
	cl_float3			normal;
	cl_float3			point;
	cl_float3			viewDir;
	cl_float3			color;
	t_object			obj;
}						t_rayHit;

typedef struct				s_ray
{
	cl_float3			o;
	cl_float3			dir;
}					t_ray;

t_env					g_env;

int						rt_main(void);
void					runLoop(void);

//DRAW

int						drawWindow(void);

// ROTATION

cl_float4				quaternionMul(cl_float4 quat_a, cl_float4 quat_b);
cl_float4				quaternionConj(cl_float4 quat);
cl_float3				quatRotWithQuat(cl_float3 vec, cl_float4 quatRotVec);
cl_float4				xyzRotToQuat(cl_float3 rotation);

// CAMERA

void					initCamera(t_camera *cam);

//KEY

void					keyHandler(SDL_Event *event);

// UTILS
cl_float3				vec3mul(cl_float3 f, float mul);
float					vec3d_length2(cl_float3 vec);
cl_float3				vec3d_unit(cl_float3 vec);
cl_float3				clFl3(float x, float y, float z);
void					debugPrintFile(void);

#endif
