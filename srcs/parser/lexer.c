#include "lexer.h"

static void			putCharInStack(char **stack, char c)
{
	int			i = 0;

	while (i < 127 && (*stack)[i])
		i++;
	if (i == 127)
		return ;
	(*stack)[i] = c;
}

static void			popCharInStack(char **stack)
{
	int			i = 0;

	while (i < 127 && (*stack)[i])
		i++;
	if (i == 127)
		return ;
	if (i > 0)
		(*stack)[i - 1] = '\0';
}

int				*currentState(void)
{
	static int		state = START;

	return (&state);
}

char				**charSaved(void)
{
	static char		*charSaved = NULL;

	if (!charSaved)
		charSaved = (char*)ft_memalloc(sizeof(char) * 128);
	return (&charSaved);
}

void				lexFile(char *file, t_error *error)
{
	int			state;
	static int		i = 0;

	state = START;
	ft_bzero(*charSaved(), 128);
	while (!g_final[state])
	{
		state = g_transit[state][(int)file[i]];
		if (state != COMMENT && state != ENTER)
			putCharInStack(charSaved(), file[i]);
		if (state == ENTER)
			error->line++;
		i++;
	}
	if (g_final[state] < 0)
	{
		i--;
		popCharInStack(charSaved());
	}
	*currentState() = ft_abs(g_final[state]) - 1;
	wordCompare(*charSaved());
	if (*currentState() == ERROR)
		dprintf(2, "line %d: lexical ERROR\n", error->line);
	
}
