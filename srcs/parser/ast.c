#include "lexer.h"
#include <stdlib.h>

void			freeAst(t_ast **ast)
{
	if (!*ast)
		return ;
	freeAst(&(*ast)->next);
	ft_strdel(&(*ast)->content);
	ft_memdel((void**)ast);
}

static t_ast		*createAst(char *content, int type)
{
	t_ast		*ast;

	ast = (t_ast*)ft_memalloc(sizeof(t_ast));
	if (content)
		ast->content = ft_strtrim(content);
	ast->type = type;
	return (ast);
}

void			addNoeud(t_ast **ast, char *content, int type)
{
	t_ast		*tmp;

	tmp = *ast;
	if (!*ast)
		*ast = createAst(content, type);
	else
	{
		while ((*ast)->next)
			*ast = (*ast)->next;
		(*ast)->next = createAst(content, type);
		*ast = tmp;
	}
}
