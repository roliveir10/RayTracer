#include "rt.h"

static void		parsOrigin(t_ast **ast)
{
	t_light		*tmp;

	tmp = g_env.light;
	while (g_env.light->next)
		g_env.light = g_env.light->next;
	for (int i = 0; i < 3; i++)
	{
		g_env.light->origin = addValueToVector(g_env.light->origin, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.light = tmp;
}

static void		parsColor(t_ast **ast)
{
	t_light		*tmp;

	tmp = g_env.light;
	while (g_env.light->next)
		g_env.light = g_env.light->next;
	for (int i = 0; i < 3; i++)
	{
		g_env.light->color = addValueToColor(g_env.light->color, (*ast)->content, i);
		*ast = (*ast)->next;
	}
	g_env.light = tmp;
}

static void		parsIntensity(char *content)
{
	t_light		*tmp;
	int		iTmp;

	tmp = g_env.light;
	while (g_env.light->next)
		g_env.light = g_env.light->next;
	iTmp = ft_atoi(content);
	g_env.light->intensity = ft_max(iTmp, 0);
	if (iTmp < 0)
		printf("Warning: intensity value in light member is invalid. Set by default to %d\n", g_env.light->intensity);
	g_env.light = tmp;
}

static void		parsType(char *content)
{
	const int	type[NBR_LIGHT_TYPE] = {POINTL, DIRECTIONAL, SPOT};
	const char	*typeString[NBR_LIGHT_TYPE] = {"\"point\"", "\"directional\"", "\"spot\""};
	t_light		*tmp;

	tmp = g_env.light;
	while (g_env.light->next)
		g_env.light = g_env.light->next;
	g_env.light->type = ft_strdup(content);
	for (int i = 0; i < NBR_LIGHT_TYPE; i++)
		if (!ft_strcmp(g_env.light->type, typeString[i]))
			g_env.light->etype = type[i];
	g_env.light = tmp;
}

static void		fillLight(int currentField, int *element, t_ast **ast)
{
	t_wordType	word[LIGHT_ELEMENT] = {
		{"\"origin\"", ORIGIN},
		{"\"color\"", COLOR},
		{"\"intensity\"", INTENSITY},
		{"\"type\"", TYPE}
	};

	if (currentField == ORIGIN)
		parsOrigin(ast);
	else if (currentField == COLOR)
		parsColor(ast);
	else if (currentField == INTENSITY)
		parsIntensity((*ast)->content);
	else if (currentField == TYPE)
		parsType((*ast)->content);
	else
		printf("Warning: invalid field in light object\n");
	for (int i = 0; i < LIGHT_ELEMENT; i++)
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
	if (element[0] && element[3])
		return (1);
	if (element[0] == 0)
		dprintf(2, "Error: origin not set for light object. Aborting...\n");
	if (element[3] == 0)
		dprintf(2, "Error: type not set for light object. Aborting...\n");
	return (0);
}

int			addValueToLight(t_ast **ast)
{
	int		element[LIGHT_ELEMENT];
	int		currentField;

	ft_bzero(&element, sizeof(int) * LIGHT_ELEMENT);
	while (*ast && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if ((*ast)->type == NUMBER || isStringValue((*ast)->type))
		{
			fillLight(currentField, element, ast);
			if (!isMemberVector(currentField))
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
