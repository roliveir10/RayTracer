#include <math.h>
#include "rt.h"

static int		fillScene(int currentField, t_ast **ast)
{
	t_wordType	word[SCENE_ELEMENT] = {
		{"\"screenX\"", SCREENX},
		{"\"screenY\"", SCREENY},
		{"\"background\"", BACKGROUND},
		{"\"maxDistToPrint\"", MAXDISTTOPRINT},
		{"\"sampleRate\"", SAMPLERATE},
		{"\"bounceMax\"", BOUNCEMAX}
	};

	for (int i = 0; i < SCENE_ELEMENT; i++)
		if (word[i].type == currentField)
			g_env.scene.parsElement[i] = 1;
	 if (currentField == SCREENX)
		g_env.scene.work_dims.x = addValueFromInt((*ast)->content);
	else if (currentField == SCREENY)
		g_env.scene.work_dims.y = addValueFromInt((*ast)->content);
	else if (currentField == BACKGROUND)
		g_env.scene.background = addValueFromColor(ast);
	else if (currentField == MAXDISTTOPRINT)
		g_env.scene.maxDistToPrint = addValueFromInt((*ast)->content);
	else if (currentField == BOUNCEMAX)
		g_env.scene.bounceMax = addValueFromInt((*ast)->content);
	else if (currentField == SAMPLERATE)
		g_env.scene.work_dims.z = addValueFromInt((*ast)->content);
	else
		{
			dprintf(2, "Error: invalid field in scene object. Aborting...\n");
			return (0);
		}
	return (1);
}

static int	fillCamera(int currentField, t_ast **ast)
{
	t_wordType	word[CAMERA_ELEMENT] = {
		{"\"fov\"", FOV},
		{"\"origin\"", ORIGIN},
		{"\"rotation\"", ROTATION}
	};

	for (int i = 0; i < CAMERA_ELEMENT; i++)
		if (word[i].type == currentField)
			g_env.scene.camera.parsElement[i] = 1;
	if (currentField == ORIGIN)
		g_env.scene.camera.origin = addValueFromVector(ast);
	else if (currentField == ROTATION)
		g_env.scene.camera.rotation = addValueFromRotation(ast);
	else if (currentField == FOV)
		g_env.scene.camera.fov = ft_max(addValueFromDouble((*ast)->content), 0) * M_PI / 180;
	else
		{
			dprintf(2, "Error: invalid field in camera object. Aborting...\n");
			return (0);
		}
	return (1);
}

static int		fillObject(int currentField, t_ast **ast)
{
	t_wordType	word[OBJECT_ELEMENT] = {
		{"\"origin\"", ORIGIN},
		{"\"color\"", COLOR},
		{"\"intensity\"", INTENSITY},
		{"\"type\"", TYPE},
		{"\"name\"", NAME},
		{"\"rotation\"", ROTATION},
		{"\"shininess\"", SHININESS},
		{"\"scale\"", SCALE},
		{"\"material\"", MATERIAL},
		{"\"limitMin\"", LIMITMIN},
		{"\"limitMax\"", LIMITMAX},
		{"\"refrac\"", REFRAC},
		{"\"opacity\"", OPACITY},
		{"\"pattern\"", PATTERN},
		{"\"bump\"", BUMP}
	};
	t_object	*curObj;

	curObj = &g_env.scene.object[g_env.scene.nbrObject];
	for (int i = 0; i < OBJECT_ELEMENT; i++)
		if (word[i].type == currentField)
			curObj->parsElement[i] = 1;

	if (currentField == NAME)
	{
		ft_strcpy(curObj->name, (*ast)->content);
		curObj->type = addValueFromPrimitiveType(curObj->name);
	}
	else if (currentField == ORIGIN)
		curObj->origin = addValueFromVector(ast);
	else if (currentField == ROTATION)
	{
		curObj->rotation = addValueFromRotation(ast);
		curObj->isRotated = 1;
	}
	else if (currentField == SCALE)
		curObj->scale = addValueFromVector(ast);
	else if (currentField == COLOR)
		curObj->color = addValueFromColor(ast);
	else if (currentField == INTENSITY)
		curObj->intensity = ft_max(addValueFromInt((*ast)->content), 0);
	else if (currentField == SHININESS)
		curObj->shininess = ft_max(addValueFromInt((*ast)->content), 0);
	else if (currentField == MATERIAL)
		curObj->material = addValueFromMaterialType((*ast)->content);
	else if (currentField == LIMITMIN)
		curObj->bboxOs.vmin = addValueFromVector(ast);
	else if (currentField == LIMITMAX)
		curObj->bboxOs.vmax = addValueFromVector(ast);
	else if (currentField == REFRAC)
		curObj->refrac = addValueFromVector(ast);
	else if (currentField == OPACITY)
		curObj->opacity = addValueFromDouble((*ast)->content);
	else if (currentField == PATTERN)
		curObj->pattern = addValueFromPatternType((*ast)->content);
	else if (currentField == BUMP)
		curObj->bump_type = addValueFromBumpType((*ast)->content);
	else
		{
			dprintf(2, "Error: invalid field in objects object. Aborting...\n");
			return (0);
		}
	return (1);
}

int		addValueFromMember(t_ast **ast, int currentObject)
{
	int	currentField;
	int	member[NBR_MEMBER] = {SCENE, CAMERA, OBJECTS};
	int	(*addValueFromElement[NBR_MEMBER])(int, t_ast **) = {fillScene, fillCamera, fillObject};
	int	ret = 1;

	if ((*ast)->type == -1)
		*ast = (*ast)->next;
	for (int i = 0; i < NBR_MEMBER; i++)
	{
		if (member[i] == currentObject)
		{
			currentObject = i;
			break ;
		}
	}
	while (*ast && ret && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if ((*ast)->type == NUMBER || isStringValue((*ast)->type))
		{
			ret = addValueFromElement[currentObject](currentField, ast);
			if (!isMemberVector(currentField))
				*ast = (*ast)->next;
		}
		else
		{
			currentField = (*ast)->type;
			*ast = (*ast)->next;
		}
	}
	return (ret);
}
