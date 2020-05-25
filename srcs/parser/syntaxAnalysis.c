#include "lexer.h"

static void		terminal(char *file, int symbol, t_error *error, t_ast **ast)
{
	if (*currentState() == symbol)
	{
		if (symbol == NUMBER)
			addNoeud(ast, *charSaved(), *currentState());
		lexFile(file, error);
	}
	else
	{
		if (isWord(symbol))	
			dprintf(2, "line %d: WORD expected\n", error->line);
		else if (symbol == COLON)
			dprintf(2, "line %d: COLON expected\n", error->line);
		else
			dprintf(2, "line %d: syntax error\n", error->line);
		error->nbrError++;
	}
}

static void		vector(char *file, t_error *error, t_ast **ast)
{
	terminal(file, SSBKT, error, ast);
	terminal(file, NUMBER, error, ast);
	terminal(file, COMMA, error, ast);
	terminal(file, NUMBER, error, ast);
	terminal(file, COMMA, error, ast);
	terminal(file, NUMBER, error, ast);
	terminal(file, ESBKT, error, ast);
}

static void		end_object(char *file, t_error *error, t_ast **ast)
{
	if (*currentState() == COMMA)
	{
		addNoeud(ast, NULL, -1);
		lexFile(file, error);
		object(file, error, ast);
		end_object(file, error, ast);
	}
}

static void		objects(char *file, t_error *error, t_ast **ast)
{
	object(file, error, ast);
	end_object(file, error, ast);
}

static void		array(char *file, t_error *error, t_ast **ast)
{
	terminal(file, SSBKT, error, ast);
	if (*currentState() == SCBKT || *currentState() == SSBKT)
		objects(file, error, ast);
	terminal(file, ESBKT, error, ast);
}

static void		stringMember(char *file, t_error *error, t_ast **ast)
{
	addNoeud(ast, *charSaved(), *currentState());
	lexFile(file, error);
	terminal(file, COLON, error, ast);
	if (isStringValue(*currentState()))
	{
		addNoeud(ast, *charSaved(), *currentState());
		lexFile(file, error);
	}
	else
		terminal(file, -1, error, ast);
}

static void		numberMember(char *file, t_error *error, t_ast **ast)
{
	addNoeud(ast, *charSaved(), *currentState());
	lexFile(file, error);
	terminal(file, COLON, error, ast);
	terminal(file, NUMBER, error, ast);
}

static void		vectorMember(char *file, t_error *error, t_ast **ast)
{
	addNoeud(ast, *charSaved(), *currentState());
	lexFile(file, error);
	terminal(file, COLON, error, ast);
	vector(file, error, ast);
}

static void		elementMember(char *file, t_error *error, t_ast **ast)
{
	addNoeud(ast, *charSaved(), *currentState());
	lexFile(file, error);
	terminal(file, COLON, error, ast);
	if (*currentState() == SSBKT)
		array(file, error, ast);
	else if (*currentState() == SCBKT)
		object(file, error, ast);
}

static void		member(char *file, t_error *error, t_ast **ast)
{
	if (isMemberString(*currentState()))
		stringMember(file, error, ast);
	else if (isMemberNumber(*currentState()))
		numberMember(file, error, ast);
	else if (isMemberVector(*currentState()))
		vectorMember(file, error, ast);
	else if (isMemberObject(*currentState()))
		elementMember(file, error, ast);
	else
		terminal(file, -1, error, ast);
}

static void		end_member(char *file, t_error *error, t_ast **ast)
{
	if (*currentState() == COMMA)
	{
		lexFile(file, error);
		member(file, error, ast);
		end_member(file, error, ast);
	}
}

static void		members(char *file, t_error *error, t_ast **ast)
{
	member(file, error, ast);
	end_member(file, error, ast);
}

void			object(char *file, t_error *error, t_ast **ast)
{
	terminal(file, SCBKT, error, ast);
	if (isWord(*currentState()))
		members(file, error, ast);
	terminal(file, ECBKT, error, ast);
}

int			syntaxAnalysis(char *file, t_ast **ast)
{
	t_error		error;

	ft_bzero(&error, sizeof(t_error));
	error.line = 1;
	initFinalTab();
	initStateTab();
	lexFile(file, &error);
	object(file, &error, ast);
	ft_strdel(charSaved());
	if (!error.nbrError && *currentState() != END)
		dprintf(2, "line: %d: illegals characters after correct expression\n", error.line);
	return (!error.nbrError && *currentState() == END);
}
