#include "rt.h"

static void		parsOrigin(t_ast **ast)
{
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	for (int i = 0; i < 3; i++)
	{
		g_env.object->origin = addValueToVector(g_env.object->origin, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.object = tmp;
}

static void		parsName(char *content)
{
	const int	type[NBR_SHAPE] = {SPHERE, PLAN, CYLINDRE, CONE, BOX};
	const char	*typeString[NBR_SHAPE] = {"\"sphere\"", "\"plan\"", "\"cylindre\"", "\"cone\"", "\"box\""};
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	g_env.object->name = ft_strdup(content);
	for (int i = 0; i < NBR_SHAPE; i++)
		if (!ft_strcmp(g_env.object->name, typeString[i]))
			g_env.object->type = type[i];
	g_env.object = tmp;
}

static void		parsLimit(t_ast **ast)
{
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	for (int i = 0; i < 6; i++)
	{
		g_env.object->limit = addValueToLimit(g_env.object->limit, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.object->isLimited = 1;
	g_env.object = tmp;
}

static void		parsSize(t_ast **ast)
{
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	for (int i = 0; i < 3; i++)
	{
		g_env.object->size = addValueToSize(g_env.object->size, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.object = tmp;
}

static void		parsRotation(t_ast **ast)
{
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	for (int i = 0; i < 3; i++)
	{
		g_env.object->rotation = addValueToVector(g_env.object->rotation, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.object = tmp;
}

static void		parsColor(t_ast **ast)
{
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	for (int i = 0; i < 3; i++)
	{
		g_env.object->color = addValueToColor(g_env.object->color, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.object = tmp;
}

static void		parsRadius(char *content)
{
	t_object	*tmp;
	double		dTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	dTmp = atof(content);
	g_env.object->radius = ft_max(dTmp, 0);
	if (dTmp <= 0)
		printf("Warning: radius lower or equal to zero for object member. Set by default to %f\n", g_env.object->radius);
	g_env.object = tmp;
}

static void		parsAngle(char *content)
{
	t_object	*tmp;
	double		dTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	dTmp = atof(content);
	g_env.object->angle = ft_max(dTmp, 0);
	if (dTmp <= 0)
		printf("Warning: radius lower or equal to null for object member\n");
	g_env.object = tmp;
}

static void		parsTexture(char *content)
{
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	g_env.object->texture = ft_strdup(content);
	g_env.object = tmp;
}

static void		parsTransparency(char *content)
{
	t_object	*tmp;
	double		dTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	dTmp = atof(content);
	g_env.object->transparency = ft_clamp(dTmp, 0, 100);
	if (dTmp < 0 || dTmp > 100)
		printf("Warning: invalid transparency value. Set by default to %f\n", g_env.object->transparency);
	g_env.object = tmp;
}

static void		parsDensity(char *content)
{
	t_object	*tmp;
	double		dTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	dTmp = atof(content);
	g_env.object->density = dTmp;
	if (dTmp < 0)
		printf("Warning: density lower than 0. Set by default to 0\n");
	g_env.object = tmp;
}

static void		parsReflection(char *content)
{
	t_object	*tmp;
	double		dTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	dTmp = atof(content);
	g_env.object->reflection = ft_clamp(dTmp, 0, 100);
	if (dTmp < 0 || dTmp > 100)
		printf("Warning: invalid transparency value. Set by default to %f\n", g_env.object->reflection);
	g_env.object = tmp;
}

static void		parsShininess(char *content)
{
	t_object	*tmp;
	int		iTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	iTmp = ft_atoi(content);
	g_env.object->shininess = ft_max(iTmp, 0);
	if (iTmp < 0)
		printf("Warning: invalid shininess value. Set by default to 0\n");
	g_env.object = tmp;
}

static void		parsShininessStrength(char *content)
{
	t_object	*tmp;
	double		dTmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	dTmp = atof(content);
	g_env.object->shininessStrength = ft_clamp(dTmp, 0, 1);
	if (dTmp < 0 || dTmp > 1)
		printf("Warning: invalid shininessStrength value. Set by default to %lf\n", g_env.object->shininessStrength);
	g_env.object = tmp;
}


static void		fillObject(int currentField, int *element, t_ast **ast)
{
	t_wordType	word[OBJECT_ELEMENT] = {
		{"\"name\"", NAME},
		{"\"origin\"", ORIGIN},
		{"\"limit\"", LIMIT},
		{"\"rotation\"", ROTATION},
		{"\"color\"", COLOR},
		{"\"radius\"", RADIUS},
		{"\"angle\"", ANGLE},
		{"\"texture\"", TEXTURE},
		{"\"transparency\"", TRANSPARENCY},
		{"\"density\"", DENSITY},
		{"\"reflection\"", REFLECTION},
		{"\"shininess\"", SHININESS},
		{"\"shininessStrength\"", SHININESSSTRENGTH},
		{"\"size\"", SIZE}
	};

	if (currentField == NAME)
		parsName((*ast)->content);
	else if (currentField == ORIGIN)
		parsOrigin(ast);
	else if (currentField == LIMIT)
		parsLimit(ast);
	else if (currentField == ROTATION)
		parsRotation(ast);
	else if (currentField == COLOR)
		parsColor(ast);
	else if (currentField == RADIUS)
		parsRadius((*ast)->content);
	else if (currentField == ANGLE)
		parsAngle((*ast)->content);
	else if (currentField == TEXTURE)
		parsTexture((*ast)->content);
	else if (currentField == TRANSPARENCY)
		parsTransparency((*ast)->content);
	else if (currentField == DENSITY)
		parsDensity((*ast)->content);
	else if (currentField == REFLECTION)
		parsReflection((*ast)->content);
	else if (currentField == SHININESS)
		parsShininess((*ast)->content);
	else if (currentField == SHININESSSTRENGTH)
		parsShininessStrength((*ast)->content);
	else if (currentField == SIZE)
		parsSize(ast);
	else
		printf("Warning: invalid field in objects object\n");
	for (int i = 0; i < OBJECT_ELEMENT; i++)
	{
		if (word[i].type == currentField)
		{
			element[i] = 1;
			break ;
		}
	}
}

static int		checkElement(int *element)
{
	t_object	*tmp;
	int		currentObject;

	tmp = g_env.object;
	if (!element[0])
	{	
		dprintf(2, "Error: missing name object. Aborting...\n");
		return (0);
	}
	else if (!element[1])
	{
		dprintf(2, "Error: origin not set for object. Aborting...\n");
		return (0);
	}
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	currentObject = g_env.object->type;
	g_env.object = tmp;
	if ((currentObject == SPHERE || currentObject == CYLINDRE) && !element[5])
	{
		dprintf(2, "Error: radius not set for object. Aborting...\n");
		return (0);
	}
	if (currentObject == CONE && !element[6])
	{
		dprintf(2, "Error: angle not set for object. Aborting...\n");
		return (0);
	}
	if (currentObject == BOX && !element[13])
	{
		dprintf(2, "Error: size not set for box object. Aborting...\n");
		return (0);
	}
	return (1);
}

int			addValueToObject(t_ast **ast)
{
	int		element[OBJECT_ELEMENT];
	int		currentField;

	ft_bzero(&element, sizeof(int) * OBJECT_ELEMENT);
	while (*ast && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if ((*ast)->type == NUMBER || isStringValue((*ast)->type))
		{
			fillObject(currentField, element, ast);
			if (!isMemberVector(currentField) && !isMemberLimit(currentField))
				*ast = (*ast)->next;
		}
		else
		{
			currentField = (*ast)->type;
			*ast = (*ast)->next;
		}
	}
	return (checkElement(element));
}
