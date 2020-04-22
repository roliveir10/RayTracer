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

int			isMemberLimit(int s)
{
	return (s >= FIRST_LIMIT_NAME && s <= LAST_LIMIT_NAME);
}

int			isStringValue(int s)
{
	return (s >= FIRST_STRING_VALUE && s <= LAST_STRING_VALUE);
}
