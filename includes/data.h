#ifndef DATA_H
# define DATA_H

# include "rt.h"

# define NBR_SHAPE 4
# define NBR_LIGHT_TYPE 3

typedef enum			s_shape
{
	SPHERE,
	PLAN,
	CYLINDRE,
	CONE
}						t_shape;

typedef enum			s_lType
{
	POINTL,
	DIRECTIONAL,
	SPOT
}						t_lType;

typedef struct			s_scene
{
	t_vector			background;
	int					screenX;
	int					screenY;
	int					sampleRate;
	int					pixPerUnit;
	int					maxDistToPrint;
	double				ambient;
	double				specular;
}						t_scene;

typedef struct			s_camera
{
	t_vector			origin;
	t_vector			rotation;
	t_vector			direction[3];
	t_vector			vpUpLeft;
	int					fov;
}						t_camera;

typedef struct			s_light
{
	int					etype;
	t_vector			origin;
	t_vector			color;
	int					intensity;
	char				*type;
	struct s_light		*next;
}						t_light;

typedef struct			s_object
{
	char				*name;
	int					type;
	t_vector			origin;
	t_vector			rotation;
	t_vector			color;
	double				radius;
	double				angle;
	char				*texture;
	double				transparency;
	double				density;
	double				reflection;
	double				shininess;
	double				shininessStrength;
	double				matRot[3][3][3];
	double				matRotInv[3][3][3];
	struct s_object		*next;
}						t_object;

typedef struct			s_nbrElement
{
	int					scene;
	int					camera;
	int					light;
	int					object;
}						t_nbrElement;

#endif
