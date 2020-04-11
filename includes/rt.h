#ifndef _RT_H
# define _RT_H

# include <stdio.h>
# include "libft.h"
# include "lexer.h"
# include "data.h"

# define SCREENX 1440
# define SCREENY 900
# define PIXELS SCREENX * SCREENY

# define NBR_KEY 1
# define NBR_ELEMENT 4

typedef enum			e_event
{
	KEYPRESSS = 2,
	REDBUTTON = 17,
	MOUSEPRESS = 4,
	KEYRELEASE = 3
}				t_event;

typedef enum			e_key
{
	KESCAP = 53,
	KLEFT,
	KRIGHT,
	KUP,
	KDOWN
}				t_key;

typedef struct			s_mlx
{
	void			*mlx;
	void			*image;
	void			*id;
	unsigned int		*mem_image;
	int			pix;
	int			size_line;
	int			endian;
}				t_mlx;

typedef struct			s_env
{
	t_mlx			mlx;
	t_scene			scene;
	t_camera		camera;
	t_light			*light;
	t_object		*object;
}				t_env;


int				rt_main(t_env *env);
char				*open_file(char *argv);
int				fillStruct(t_env *env, t_ast *ast);
#endif
