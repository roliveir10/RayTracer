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

static void			wordCompare(char *charSaved)
{
	t_wordType		wordType[NBR_WORD] = {
		{"\"scene\"", SCENE}, {"\"camera\"", CAMERA}, {"\"light\"", LIGHT},
		{"\"object\"", OBJECTS}, {"\"specular\"", SPECULAR}, {"\"ambient\"", AMBIENT},
		{"\"origin\"", ORIGIN}, {"\"rotation\"", ROTATION},
		{"\"angle\"", ANGLE}, {"\"color\"", COLOR}, {"\"type\"", TYPE},
		{"\"name\"", NAME}, {"\"radius\"", RADIUS}, {"\"reflection\"", REFLECTION},
		{"\"density\"", DENSITY}, {"\"texture\"", TEXTURE},
		{"\"transparency\"", TRANSPARENCY}, {"\"point\"", LPOINT}, {"\"directional\"", LDIR},
		{"\"spot\"", LSPOT}, {"\"sphere\"", SSPHERE}, {"\"cone\"", SCONE},
		{"\"plan\"", SPLAN}, {"\"cylindre\"", SCYLINDRE},
		{"\"background\"", BACKGROUND}, {"\"screenX\"", SCREENX},
		{"\"screenY\"", SCREENY}, {"\"fov\"", FOV}, {"\"sampleRate\"", SAMPLERATE},
		{"\"pixPerUnit\"", PIXPERUNIT}, {"\"maxDistToPrint\"", MAXDISTTOPRINT},
		{"\"shininess\"", SHININESS}, {"\"shininessStrength\"", SHININESSSTRENGTH}
	};
	char			*tmp;

	if (*currentState() == WORD)
	{
		for (int j = 0; j < NBR_WORD; j++)
		{
			tmp = ft_strtrim(charSaved);
			if (!ft_strcmp(tmp, wordType[j].lexeme))
			{
				*currentState() = wordType[j].type;
				ft_strdel(&tmp);
				break ;
			}
			ft_strdel(&tmp);
		}
		if (*currentState() == WORD)
			*currentState() = ERROR;
	}
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
		putCharInStack(charSaved(), file[i]);
		if (file[i] == '\n')
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
