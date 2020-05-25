#include "rt.h"

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
		return (1);
	rt_main();
	return (0);
}
