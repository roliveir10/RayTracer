#include "rt.h"

static void			freeLight(t_light **light)
{
	if (!*light)
		return ;
	freeLight(&(*light)->next);
	if ((*light)->type)
		ft_strdel(&(*light)->type);
	ft_memdel((void**)light);
}

static void			freeObject(t_object **object)
{
	if (!*object)
		return ;
	freeObject(&(*object)->next);
	if ((*object)->name)
		ft_strdel(&(*object)->name);
	if ((*object)->texture)
		ft_strdel(&(*object)->texture);
	ft_memdel((void**)object);
}

static void			freeStruct(t_env *env)
{
	if (env->light)
		freeLight(&env->light);
	if (env->object)
		freeObject(&env->object);
}

int				main(int argc, char **argv)
{
	t_env			env;
	char			*file;
	int			analysis;
	t_ast			*ast;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./RT file.json\n", 2);
		return (1);
	}
	ft_bzero(&env, sizeof(t_env));
	ft_bzero(&ast, sizeof(t_ast));
	if (!(file = open_file(argv[1])))
		return (1);
	analysis = syntaxAnalysis(file, &ast);
	ft_strdel(&file);
	if (!analysis)
	{
		freeAst(&ast);
		return (1);
	}
	analysis = fillStruct(&env, ast);
	freeAst(&ast);
	if (!analysis)
		return (1);
	//rt_main(&env);
	freeStruct(&env);
	return (0);
}
