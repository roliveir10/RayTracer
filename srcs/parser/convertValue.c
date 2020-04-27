#include "rt.h"
#include <stdlib.h>
#include <math.h>

t_vector			addValueFromVector(t_ast **ast)
{
	t_vector		new;

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			new.x = atof((*ast)->content);
		else if (i == 1)
			new.y = atof((*ast)->content);
		else if (i == 2)
			new.z = atof((*ast)->content);
		*ast = (*ast)->next;
	}
	return (new);
}

t_vector			addValueFromSize(t_ast **ast)
{
	t_vector		new;
	double			value;

	for (int i = 0; i < 3; i++)
	{
		value = atof((*ast)->content);
		if (i == 0)
			new.x = ft_max(value, 0);
		else if (i == 1)
			new.y = ft_max(value, 0);
		else if (i == 2)
			new.z = ft_max(value, 0);
		*ast = (*ast)->next;
	}
	return (new);
}

t_vector			addValueFromColor(t_ast **ast)
{
	t_vector		new;
	double			dTmp;

	for (int i = 0; i < 3; i++)
	{
		dTmp = atof((*ast)->content);
		if (i == 0)
			new.x = ft_clamp(dTmp / 255, 0, 1);
		else if (i == 1)
			new.y = ft_clamp(dTmp / 255, 0, 1);
		else if (i == 2)
			new.z = ft_clamp(dTmp / 255, 0, 1);
		*ast = (*ast)->next;
	}
	return (new);
}

t_limit				addValueFromLimit(t_ast **ast)
{
	t_limit			new;
	double			dTmp;

	for (int i = 0; i < 6; i++)
	{
		dTmp = atof((*ast)->content);
		if (i == 0)
			new.x = dTmp;
		else if (i == 1)
			new.y = dTmp;
		else if (i == 2)
			new.z = dTmp;
		else if (i == 3)
			new.sizeX = ft_max(dTmp, 0);
		else if (i == 4)
			new.sizeY = ft_max(dTmp, 0);
		else if (i == 5)
			new.sizeZ = ft_max(dTmp, 0);
		*ast = (*ast)->next;
	}
	return (new);
}

double				addValueFromDouble(char *content)
{
	double			dTmp;

	dTmp = atof(content);
	return (dTmp);
}

int				addValueFromInt(char *content)
{
	int			iTmp;

	iTmp = ft_atoi(content);
	return (iTmp);
}

char				*addValueFromString(char *content)
{
	return (ft_strdup(content));
}

int				addValueFromLightType(char *toCompare)
{
	const int		type[NBR_LIGHT_TYPE] = {POINTL, DIRECTIONAL, SPOT};
	const char		*typeString[NBR_LIGHT_TYPE] = {"\"point\"", "\"directional\"", "\"spot\""};

	for (int i = 0; i < NBR_LIGHT_TYPE; i++)
		if (!ft_strcmp(toCompare, typeString[i]))
			return (type[i]);
	return (-1);
}

int				addValueFromObjectType(char *toCompare)
{
	const int		type[NBR_SHAPE] = {SPHERE, PLAN, CYLINDRE, CONE, BOX};
	const char		*typeString[NBR_SHAPE] = {"\"sphere\"", "\"plan\"",
		"\"cylindre\"", "\"cone\"", "\"box\""};

	for (int i = 0; i < NBR_SHAPE; i++)
		if (!ft_strcmp(toCompare, typeString[i]))
			return (type[i]);
	return (-1);
}
