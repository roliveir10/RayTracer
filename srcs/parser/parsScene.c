#include "rt.h"

static void		parsAmbient(char *content)
{
	double		dTmp;

	dTmp = atof(content);
	g_env.scene.ambient = ft_clamp(dTmp, 0, 1);
	if (dTmp < 0 || dTmp > 1)
		printf("Warning: ambient value is invalid. Set by default to %f\n", g_env.scene.ambient);
}

static void		parsScreen(char *content, int currentField)
{
	int		iTmp;

	iTmp = ft_atoi(content);
	if (iTmp <= 0)
	{
		g_env.scene.screenX = 1260;
		g_env.scene.screenY = 810;
		printf("Warning: screen size values are invalids. Set by default to screenX %d | screenY %d\n", g_env.scene.screenX, g_env.scene.screenY);
	}
	if (currentField == SCREENX)
		g_env.scene.screenX = iTmp > 0 ? iTmp : 1260;
	else
		g_env.scene.screenY = iTmp > 0 ? iTmp : 810;
}

static void		parsSampleRate(char *content)
{
	int		iTmp;

	iTmp = ft_atoi(content);
	g_env.scene.sampleRate = ft_max(iTmp, 1);
	if (iTmp < g_env.scene.sampleRate)
		printf("Warning: sampleRate value is invalid. Set by default to %d\n", g_env.scene.sampleRate);
}

static void		parsPixPerUnit(char *content)
{
	int		iTmp;

	iTmp = ft_atoi(content);
	g_env.scene.pixPerUnit = ft_max(iTmp, 1);
	if (iTmp < g_env.scene.pixPerUnit)
		printf("Warning: pixPerUnit value is invalid. Set by default to %d\n", g_env.scene.pixPerUnit);
}

static void		parsMaxDistToPrint(char *content)
{
	int		iTmp;

	iTmp = atof(content);
	g_env.scene.maxDistToPrint = iTmp <= 0 ? 15000 : iTmp;
	if (iTmp <= 0)
		printf("Warning: maxDistToPrint value is invalid. Set by default to %d\n", g_env.scene.maxDistToPrint);
}

static void		parsFov(char *content)
{
	double		dTmp;

	dTmp = atof(content);
	g_env.camera.fov = dTmp <= 0 ? 10 : dTmp;
	if (dTmp <= 0)
		printf("Warning: fov value is invalid. Set by default to %lf\n", g_env.camera.fov);
}

static void		parsBackground(t_ast **ast)
{
	for (int i = 0; i < 3; i++)
	{
		g_env.scene.background = addValueToColor(g_env.scene.background, (*ast)->content, i);
		*ast = (*ast)->next;
	}
}

static void		fillScene(int currentField, int *element, t_ast **ast)
{
	t_wordType	word[SCENE_ELEMENT] = {
		{"\"ambient\"", AMBIENT},
		{"\"screenX\"", SCREENX},
		{"\"screenY\"", SCREENY},
		{"\"sampleRate\"", SAMPLERATE},
		{"\"pixPerUnit\"", PIXPERUNIT},
		{"\"maxDistToPrint\"", MAXDISTTOPRINT},
		{"\"fov\"", FOV},
		{"\"background\"", BACKGROUND}
	};

	if (currentField == AMBIENT)
		parsAmbient((*ast)->content);
	else if (currentField == SCREENX || currentField == SCREENY)
		parsScreen((*ast)->content, currentField);
	else if (currentField == SAMPLERATE)
		parsSampleRate((*ast)->content);
	else if (currentField == PIXPERUNIT)
		parsPixPerUnit((*ast)->content);
	else if (currentField == MAXDISTTOPRINT)
		parsMaxDistToPrint((*ast)->content);
	else if (currentField == FOV)
		parsFov((*ast)->content);
	else if (currentField == BACKGROUND)
		parsBackground(ast);
	else
		printf("Warning: invalid field in scene object\n");
	for (int i = 0; i < SCENE_ELEMENT; i++)
		if (word[i].type == currentField)
		{
			element[i] = 1;
			break ;
		}
}

static int		checkElement(int *element)
{
	if (!element[1] || !element[2])
		printf("Warning: screen size values are invalids. Set by default to screenX %d | screenY %d\n", g_env.scene.screenX, g_env.scene.screenY);
	if (!element[3])
		printf("Warning: sampleRate value is missing. Set by default to %d\n", g_env.scene.sampleRate);
	if (!element[4])
		printf("Warning: pixPerUnit value is missing. Set by default to %d\n", g_env.scene.pixPerUnit);
	if (!element[5])
		printf("Warning: maxDistToPrint value is missing. Set by default to %d\n", g_env.scene.maxDistToPrint);
	if (!element[6])
		printf("Warning: fov value is invalid. Set by default to %lf\n", g_env.camera.fov);
	return (1);
}

int			addValueToScene(t_ast **ast)
{
	int		element[SCENE_ELEMENT];
	int		currentField;

	ft_bzero(&element, sizeof(int) * SCENE_ELEMENT);
	while (*ast && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if ((*ast)->type == NUMBER || isStringValue((*ast)->type))
		{
			fillScene(currentField, element, ast);
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


