#include "rt.h"

static int		printErrorRecommendation(char *name, int value)
{
	dprintf(2, "Error: %s value is not set or invalid. Recommended value: %d. Aborting...\n", name, value);
	return (0);
}

static int		printError(char *name)
{
	dprintf(2, "Error: %s value is not set or invalid. Aborting...\n", name);
	return (0);
}

static int		sceneCheck(__unused int *element)
{
	int		ret = 1;

	if (g_env.scene.screenX <= SCREEN_MIN)
		ret = printErrorRecommendation("screenX", 1260);
	if (g_env.scene.screenY <= SCREEN_MIN)
		ret = printErrorRecommendation("screenY", 810);
	if (g_env.scene.sampleRate < 1)
		g_env.scene.sampleRate = 1;
	if (g_env.scene.pixPerUnit < 1)
		g_env.scene.pixPerUnit = 1;
	if (g_env.scene.maxDistToPrint <= 0)
		g_env.scene.maxDistToPrint = 1;
	if (g_env.camera.fov <= 0)
		g_env.camera.fov = 5;
	return (ret);
}

static int		cameraCheck(int *element)
{
	int		ret = 1;

	if (!element[8])
		ret = printError("camera's origin");
	return (ret);
}

static int		lightCheck(int *element)
{
	int		ret = 1;
	t_light		*tmp;

	tmp = g_env.light;
	while (g_env.light->next)
		g_env.light = g_env.light->next;
	if (!element[10])
		ret = printError("light's origin");
	if (g_env.light->etype == -1)
		ret = printError("light's type");
	g_env.light = tmp;
	return (ret);
}

static int		objectCheck(int *element)
{
	int		ret = 1;
	t_object	*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	if (!element[14] || g_env.object->type == -1)
		ret = printError("object's name");
	if (!element[15])
		ret = printError("object's origin");
	if (!g_env.object->limit.sizeX && !g_env.object->limit.sizeY && !g_env.object->limit.sizeZ)
		g_env.object->isLimited = 0;
	if ((g_env.object->type == SPHERE || g_env.object->type == CYLINDRE) && g_env.object->radius <= 0)
		ret = printError("radius for sphere or cylindre");
	if (g_env.object->type == CONE && !element[20])
		ret = printError("cone's angle");
	g_env.object = tmp;
	return (ret);
}

int		checkElement(int currentObject, int *element)
{
	int	(*checker[NBR_OBJECT])(int*) = {sceneCheck, cameraCheck,
		lightCheck, objectCheck};

	return (checker[currentObject](element));

}

int		checkObjectMultiplication(int *object, int currentObject)
{
	int	type[NBR_OBJECT] = {SCENE, CAMERA, LIGHT, OBJECTS};

	for (int i = 0; i < NBR_OBJECT; i++)
		if (type[i] == currentObject)
		{
			currentObject = i;
			break ;
		}
	if (object[currentObject] == 1)
	{
		dprintf(2, "Error: multiplication of same objects in the files. Aborting...\n");
		return (0);
	}
	object[currentObject] = 1;
	return (1);
}

int		checkObject(int *object)
{
	if (!object[0])
	{
		dprintf(2, "Error: scene field is missing. Aborting...\n");
		return (0);
	}
	if (!object[1])
	{
		dprintf(2, "Error: camera field is missing. Aborting...\n");
		return (0);
	}
	if (!object[2])
		printf("Warning: no light in the file\n");
	else if (!object[3])
		printf("Warning: no object in the file\n");
	return (1);
}
