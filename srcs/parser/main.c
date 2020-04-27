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

void				freeStruct()
{
	if (g_env.light)
		freeLight(&g_env.light);
	if (g_env.object)
		freeObject(&g_env.object);
}

int					main(int argc, char **argv)
{
	char			*file;
	int			analysis;
	t_ast			*ast;

	if (argc != 2)
	{
		ft_putstr_fd("usage: ./RT file.json\n", 2);
		return (1);
	}
	ft_bzero(&g_env, sizeof(t_env));
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
	analysis = fillStruct(ast);
	freeAst(&ast);
	if (!analysis)
	{
		freeStruct();
		return (1);
	}
	rt_main();
	return (0);
}
