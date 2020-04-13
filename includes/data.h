#ifndef DATA_H
# define DATA_H

# include "rt.h"

typedef struct			s_scene
{
	double				ambient;
	double				specular;
}						t_scene;

typedef struct			s_camera
{
	t_vector			origin;
	t_vector			rotation;
	t_vector			direction[3];
	t_vector			vpUpLeft;
}						t_camera;

typedef struct			s_light
{
	t_vector			origin;
	t_vector			color;
	t_vector			direction;
	char				*type;
	struct s_light		*next;
}						t_light;

typedef struct			s_object
{
	char				*name;
	t_vector			origin;
	t_vector			rotation;
	t_vector			color;
	double				radius;
	double				angle;
	char				*texture;
	double				transparency;
	double				density;
	double				reflection;
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
