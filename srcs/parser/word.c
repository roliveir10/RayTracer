#include "lexer.h"

void				wordCompare(char *charSaved)
{
	t_wordType		wordType[NBR_WORD] = {
		{"\"scene\"", SCENE},
		{"\"camera\"", CAMERA},
		{"\"light\"", LIGHT},
		{"\"object\"", OBJECTS},
		{"\"ambient\"", AMBIENT},
		{"\"origin\"", ORIGIN},
		{"\"rotation\"", ROTATION},
		{"\"angle\"", ANGLE},
		{"\"color\"", COLOR},
		{"\"type\"", TYPE},
		{"\"name\"", NAME},
		{"\"radius\"", RADIUS},
		{"\"reflection\"", REFLECTION},
		{"\"density\"", DENSITY},
		{"\"texture\"", TEXTURE},
		{"\"transparency\"", TRANSPARENCY},
		{"\"point\"", LPOINT},
		{"\"directional\"", LDIR},
		{"\"spot\"", LSPOT},
		{"\"sphere\"", SSPHERE},
		{"\"cone\"", SCONE},
		{"\"plan\"", SPLAN},
		{"\"cylindre\"", SCYLINDRE},
		{"\"background\"", BACKGROUND},
		{"\"screenX\"", SCREENX},
		{"\"screenY\"", SCREENY},
		{"\"fov\"", FOV},
		{"\"sampleRate\"", SAMPLERATE},
		{"\"pixPerUnit\"", PIXPERUNIT},
		{"\"maxDistToPrint\"", MAXDISTTOPRINT},
		{"\"shininess\"", SHININESS},
		{"\"shininessStrength\"", SHININESSSTRENGTH},
		{"\"intensity\"", INTENSITY},
		{"\"limit\"", LIMIT},
		{"\"box\"", SBOX},
		{"\"size\"", SIZE}
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
