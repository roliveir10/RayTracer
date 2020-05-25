#include "rt.h"
#include <stdlib.h>
#include <math.h>

cl_float3			addValueFromVector(t_ast **ast)
{
	cl_float3		new;

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

cl_float3			addValueFromRotation(t_ast **ast)
{
	cl_float3		new;

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			new.x = atof((*ast)->content) * M_PI / 180;
		else if (i == 1)
			new.y = atof((*ast)->content) * M_PI / 180;
		else if (i == 2)
			new.z = atof((*ast)->content) * M_PI / 180;
		*ast = (*ast)->next;
	}
	return (new);
}

cl_float3			addValueFromColor(t_ast **ast)
{
	cl_float3		new;
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

int				addValueFromPrimitiveType(char *toCompare)
{
	const int		type[PRIMITIVES] = {SPHERE, PLAN, CYLINDRE, CONE, BOX, DISK, HYPERBOLOID};
	const char		*typeString[PRIMITIVES] = {
			"\"sphere\"",
			"\"plan\"",
			"\"cylindre\"",
			"\"cone\"",
			"\"box\"",
			"\"disk\"",
			"\"hyperboloid\""
	};

	for (int i = 0; i < PRIMITIVES; i++)
		if (!ft_strcmp(toCompare, typeString[i]))
			return (type[i]);
	return (SNONE);
}

int				addValueFromMaterialType(char *toCompare)
{
	const int	type[MATERIALS] = {MLIGHT, MDIFFUSE, MTRANSPARENT, MSPECULAR};
	const char	*typeString[MATERIALS] = {
			"\"light\"",
			"\"diffuse\"",
			"\"transparent\"",
			"\"specular\""
	};

	for (int i = 0; i < MATERIALS; i++)
		if (!ft_strcmp(toCompare, typeString[i]))
			return (type[i]);
	return (MNONE);
}

int				addValueFromPatternType(char *toCompare)
{
	const int	type[PATTERNS] = {PSOLID};
	const char	*typeString[PATTERNS] = {
			"\"solid\""
	};

	for (int i = 0; i < PATTERNS; i++)
		if (!ft_strcmp(toCompare, typeString[i]))
			return (type[i]);
	return (PSOLID);
}

int				addValueFromBumpType(char *toCompare)
{
	const int	type[BUMP] = {BFLAT, BBUMP};
	const char	*typeString[BUMP] = {
			"\"flat\"",
			"\"bump\""
	};

	for (int i = 0; i < BUMP; i++)
		if (!ft_strcmp(toCompare, typeString[i]))
			return (type[i]);
	return (BFLAT);
}
