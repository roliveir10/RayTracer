#include "lexer.h"

int			isWord(int s)
{
	return (s >= FIRST_WORD_STATE && s <= LAST_WORD_STATE);
}

int			isMemberString(int s)
{
	return (s >= FIRST_STRING_NAME && s <= LAST_STRING_NAME);
}

int			isMemberVector(int s)
{
	return (s >= FIRST_VECTOR_NAME && s <= LAST_VECTOR_NAME);
}

int			isMemberNumber(int s)
{
	return (s >= FIRST_NUMBER_NAME && s <= LAST_NUMBER_NAME);
}

int			isMemberObject(int s)
{
	return (s >= FIRST_OBJECTS_NAME && s <= LAST_OBJECTS_NAME);
}

int			isStringValue(int s)
{
	return (s >= FIRST_STRING_VALUE && s <= LAST_STRING_VALUE);
}

char			*stateToWord(int state)
{
	const char	*word[NBR_STATE + NBR_WORD] = {
		"start", "scbkt", "sword", "letter", "word", "colon",
		"digit", "number", "point", "fdigit", "comma", "ecbkt",
		"ssbkt", "esbkt", "minus", "comment", "enter", "end",
		"scene", "camera", "objects", "type", "material", "pattern",
		"bumpType", "name", "origin", "rotation", "background", "color",
		"scale", "limitMin", "limitMax", "refrac", "shininess",
		"intensity", "screenX", "screenY", "fov", "sampleRate",
		"maxDistToPrint", "bounceMax", "ssphere", "scone", "splan",
		"scylindre", "scube", "sdisk", "shyperboloid", "sinfhyperboloid",
		"sinfcylindre",
		"sinfcone", "srectangle", "striangle", "sparaboloid", "ssaddle",
		"sthorus", "scapsule", "sellipsoid", "sroundedcone", "ssphere4",
		"sgoursat", "sroundedbox", "slight",
		"sdiffuse", "stransparent", "sspecular", "ssolid", "sflat",
		"sbump", "error"
		};
	
	if (state >= NBR_STATE + NBR_WORD)
		return (NULL);
	return (ft_strdup(word[state]));
}
