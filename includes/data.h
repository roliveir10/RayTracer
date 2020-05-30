#ifndef DATA_H
# define DATA_H

# include "rt.h"
# include "cl.h"

# define SCENE_ELEMENT 6
# define CAMERA_ELEMENT 3
# define OBJECT_ELEMENT 15
# define ELEMENT SCENE_ELEMENT + CAMERA_ELEMENT + LIGHT_ELEMENT + OBJECT_ELEMENT
# define NBR_MEMBER 3

# define MAX_OBJECT 64

# define PRIMITIVES 21
typedef enum			e_objType
{
	SNONE = -1,
	SPHERE,
	PLAN,
	CYLINDRE,
	CONE,
	CUBE,
	DISK,
	HYPERBOLOID,
	INFHYPERBOLOID,
	INFCYLINDRE,
	INFCONE,
	RECTANGLE,
	TRIANGLE,
	PARABOLOID,
	SADDLE,
	THORUS,
	CAPSULE,
	ELLIPSOID,
	ROUNDEDCONE,
	SPHERE4,
	GOURSAT,
	ROUNDEDBOX
}						t_objType;

typedef struct			s_camera
{
	cl_float3			origin;
	cl_float3			rotation;
	cl_float3			direction[3];
	cl_float3			vpUpLeft;
	float				fov;
	float				planeDist;
	float				viewPlaneWidth;
	float				viewPlaneHeight;
	float				xIndent;
	float				yIndent;
	char				parsElement[CAMERA_ELEMENT];
}						t_camera;

typedef struct			s_bbox
{
	cl_float3			vmin;
	cl_float3			vmax;
}						t_bbox;

# define MATERIALS 5
typedef enum			s_material
{
	MNONE = -1,
	MLIGHT,
	MDIFFUSE,
	MTRANSPARENT,
	MSPECULAR
}						t_material;

# define PATTERNS 1
typedef enum			e_pattern
{
	PSOLID = 0
}						t_pattern;

# define BUMP 2
typedef enum			e_bump
{
	BFLAT,
	BBUMP
}						t_bump;

typedef struct			s_object
{
	char				name[16];
	t_objType			type;
	t_material			material;
	cl_float3			origin;
	cl_float3			color;
	int					intensity;
	cl_float3			rotation;
	char				isRotated;
	cl_float3			scale;
	t_bbox				bboxOs;
	t_bbox				bboxWs;
	cl_float			shininess;
	cl_float3			refrac;
	cl_float			opacity;
	cl_float16			w_to_o;
	cl_float16			o_to_w;
	cl_float16			n_to_w;
	t_pattern			pattern;
	t_bump				bump_type;
	char				parsElement[OBJECT_ELEMENT];
}						t_object;

typedef struct			s_scene
{
	cl_float3			background;
	t_camera			camera;
	t_object			object[MAX_OBJECT];
	int					nbrObject;
	float				maxDistToPrint;
	t_bbox				bboxWs;
	int					bounceMax;
	cl_int3				work_steps;
	cl_int3				work_dims;
	char				parsElement[SCENE_ELEMENT];
}						t_scene;
#endif
