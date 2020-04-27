#include <math.h>
#include "rt.h"

static void		fillElementChecker(int currentField, int *element, int min, int max)
{
	t_wordType	word[ELEMENT] = {
		{"\"ambient\"", AMBIENT},
		{"\"screenX\"", SCREENX},
		{"\"screenY\"", SCREENY},
		{"\"sampleRate\"", SAMPLERATE},
		{"\"pixPerUnit\"", PIXPERUNIT},
		{"\"maxDistToPrint\"", MAXDISTTOPRINT},
		{"\"fov\"", FOV},
		{"\"background\"", BACKGROUND},
		{"\"origin\"", ORIGIN},
		{"\"rotation\"", ROTATION},
		{"\"origin\"", ORIGIN},
		{"\"color\"", COLOR},
		{"\"intensity\"", INTENSITY},
		{"\"type\"", TYPE},
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

	for (int i = min; i < max; i++)
	{
		if (word[i].type == currentField)
		{
			element[i] = 1;
			break ;
		}
	}
}

static int		fillScene(int currentField, int *element, t_ast **ast)
{
	if (currentField == AMBIENT)
		g_env.scene.ambient = ft_clamp(addValueFromDouble((*ast)->content), 0, 1);
	else if (currentField == SCREENX)
		g_env.scene.screenX = addValueFromInt((*ast)->content);
	else if (currentField == SCREENY)
		g_env.scene.screenY = addValueFromInt((*ast)->content);
	else if (currentField == SAMPLERATE)
		g_env.scene.sampleRate = ft_max(addValueFromInt((*ast)->content), 1);
	else if (currentField == PIXPERUNIT)
		g_env.scene.pixPerUnit = ft_max(addValueFromInt((*ast)->content), 1);
	else if (currentField == MAXDISTTOPRINT)
		g_env.scene.maxDistToPrint = ft_max(addValueFromInt((*ast)->content), 1);
	else if (currentField == FOV)
		g_env.camera.fov = ft_max(addValueFromDouble((*ast)->content), 0);
	else if (currentField == BACKGROUND)
		g_env.scene.background = addValueFromColor(ast);
	else
		{
			dprintf(2, "Error: invalid field in scene object. Aborting...\n");
			return (0);
		}
	fillElementChecker(currentField, element,  0, SCENE_ELEMENT);
	return (1);
}

static int	fillCamera(int currentField, int *element, t_ast **ast)
{
	if (currentField == ORIGIN)
		g_env.camera.origin = addValueFromVector(ast);
	else if (currentField == ROTATION)
		g_env.camera.rotation = addValueFromVector(ast);
	else
		{
			dprintf(2, "Error: invalid field in camera object. Aborting...\n");
			return (0);
		}
	fillElementChecker(currentField, element, SCENE_ELEMENT, SCENE_ELEMENT + CAMERA_ELEMENT);
	return (1);
}

static int		fillLight(int currentField, int *element, t_ast **ast)
{
	t_light		*tmp;

	tmp = g_env.light;
	while (g_env.light->next)
		g_env.light = g_env.light->next;
	if (currentField == ORIGIN)
		g_env.light->origin = addValueFromVector(ast);
	else if (currentField == COLOR)
		g_env.light->color = addValueFromColor(ast);
	else if (currentField == INTENSITY)
		g_env.light->intensity = ft_max(addValueFromInt((*ast)->content), 0);
	else if (currentField == TYPE)
	{
		g_env.light->type = addValueFromString((*ast)->content);
		g_env.light->etype = addValueFromLightType(g_env.light->type);
	}
	else
	{
		dprintf(2, "Error: invalid field in light object. Aborting...\n");
		return (0);
	}
	fillElementChecker(currentField, element, SCENE_ELEMENT + CAMERA_ELEMENT, ELEMENT - OBJECT_ELEMENT);
	g_env.light = tmp;
	return (1);
}

static int		fillObject(int currentField, int *element, t_ast **ast)
{
	t_object	*tmp;;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	if (currentField == NAME)
	{
		g_env.object->name = addValueFromString((*ast)->content);
		g_env.object->type = addValueFromObjectType(g_env.object->name);
	}
	else if (currentField == ORIGIN)
		g_env.object->origin = addValueFromVector(ast);
	else if (currentField == LIMIT)
	{
		g_env.object->limit = addValueFromLimit(ast);
		g_env.object->isLimited = 1;
	}
	else if (currentField == ROTATION)
		g_env.object->rotation = addValueFromVector(ast);
	else if (currentField == COLOR)
		g_env.object->color = addValueFromColor(ast);
	else if (currentField == RADIUS)
		g_env.object->radius = addValueFromDouble((*ast)->content);
	else if (currentField == ANGLE)
		g_env.object->angle = addValueFromDouble((*ast)->content) * M_PI / 180;
	else if (currentField == TEXTURE)
		g_env.object->texture = addValueFromString((*ast)->content);
	else if (currentField == TRANSPARENCY)
		g_env.object->transparency = addValueFromDouble((*ast)->content);
	else if (currentField == DENSITY)
		g_env.object->density = addValueFromDouble((*ast)->content);
	else if (currentField == REFLECTION)
		g_env.object->reflection = addValueFromDouble((*ast)->content);
	else if (currentField == SHININESS)
		g_env.object->shininess = ft_max(addValueFromInt((*ast)->content), 0);
	else if (currentField == SHININESSSTRENGTH)
		g_env.object->shininessStrength = ft_clamp(addValueFromDouble((*ast)->content), 0, 1);
	else if (currentField == SIZE)
		g_env.object->size = addValueFromSize(ast);
	else
		{
			dprintf(2, "Error: invalid field in objects object. Aborting...\n");
			g_env.object = tmp;
			return (0);
		}
	fillElementChecker(currentField, element, ELEMENT - OBJECT_ELEMENT, ELEMENT);
	
	g_env.object = tmp;
	return (1);
}

int		addValueFromMember(t_ast **ast, int currentObject)
{
	int	element[ELEMENT];
	int	currentField;
	int	object[NBR_OBJECT] = {SCENE, CAMERA, LIGHT, OBJECTS};
	int	(*addValueFromElement[NBR_OBJECT])(int, int*, t_ast **) = {fillScene, fillCamera, fillLight, fillObject};
	int	ret;

	ret = 1;
	if ((*ast)->type == -1)
		*ast = (*ast)->next;
	for (int i = 0; i < NBR_OBJECT; i++)
	{
		if (object[i] == currentObject)
		{
			currentObject = i;
			break ;
		}
	}
	ft_bzero(&element, sizeof(int) * ELEMENT);
	while (*ast && ret && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if ((*ast)->type == NUMBER || isStringValue((*ast)->type))
		{
			ret = addValueFromElement[currentObject](currentField, element, ast);
			if (!isMemberVector(currentField) && !isMemberLimit(currentField))
				*ast = (*ast)->next;
		}
		else
		{
			currentField = (*ast)->type;
			*ast = (*ast)->next;
		}
	}
	if (ret)
		ret = checkElement(currentObject, element);
	return (ret);
}
