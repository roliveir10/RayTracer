#include "lexer.h"

void				wordCompare(char *charSaved)
{
	t_wordType		wordType[NBR_WORD] = {
		{"\"scene\"", SCENE},
		{"\"camera\"", CAMERA},
		{"\"object\"", OBJECTS},
		{"\"origin\"", ORIGIN},
		{"\"rotation\"", ROTATION},
		{"\"color\"", COLOR},
		{"\"type\"", TYPE},
		{"\"name\"", NAME},
		{"\"sphere\"", SSPHERE},
		{"\"cone\"", SCONE},
		{"\"plan\"", SPLAN},
		{"\"cylindre\"", SCYLINDRE},
		{"\"cube\"", SCUBE},
		{"\"hyperboloid\"", SHYPERBOLOID},
		{"\"infhyperboloid\"", SINFHYPERBOLOID},
		{"\"disk\"", SDISK},
		{"\"infcylindre\"", SINFCYLINDRE},
		{"\"infcone\"", SINFCONE},
		{"\"rectangle\"", SRECTANGLE},
		{"\"triangle\"", STRIANGLE},
		{"\"paraboloid\"", SPARABOLOID},
		{"\"saddle\"", SSADDLE},
		{"\"thorus\"", STHORUS},
		{"\"capsule\"", SCAPSULE},
		{"\"ellipsoid\"", SELLIPSOID},
		{"\"roundedcone\"", SROUNDEDCONE},
		{"\"sphere4\"", SSPHERE4},
		{"\"goursat\"", SGOURSAT},
		{"\"roundedbox\"", SROUNDEDBOX},
		{"\"background\"", BACKGROUND},
		{"\"screenX\"", SCREENX},
		{"\"screenY\"", SCREENY},
		{"\"fov\"", FOV},
		{"\"sampleRate\"", SAMPLERATE},
		{"\"maxDistToPrint\"", MAXDISTTOPRINT},
		{"\"shininess\"", SHININESS},
		{"\"intensity\"", INTENSITY},
		{"\"scale\"", SCALE},
		{"\"bounceMax\"", BOUNCEMAX},
		{"\"material\"", MATERIAL},
		{"\"limitMin\"", LIMITMIN},
		{"\"limitMax\"", LIMITMAX},
		{"\"refrac\"", REFRAC},
		{"\"opacity\"", OPACITY},
		{"\"pattern\"", PATTERN},
		{"\"bumpType\"", BUMPTYPE},
		{"\"light\"", SLIGHT},
		{"\"diffuse\"", SDIFFUSE},
		{"\"transparent\"", STRANSPARENT},
		{"\"specular\"", SSPECULAR},
		{"\"solid\"", SSOLID},
		{"\"flat\"", SFLAT},
		{"\"bump\"", SBUMP}
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
