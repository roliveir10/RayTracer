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

static void		printWarning(char *name, int value)
{
	printf("Warning: %s value is invalid. Set by default to %d\n", name, value);
}

static int		sceneCheck(void)
{
	int		ret = 1;

	if (g_env.scene.work_dims.x <= SCREEN_MIN)
		ret = printErrorRecommendation("screenX", DEFAULT_SCREENX);
	if (g_env.scene.work_dims.y <= SCREEN_MIN)
		ret = printErrorRecommendation("screenY", DEFAULT_SCREENY);
	if (g_env.scene.work_dims.z < 1)
	{
		printWarning("sampleRate", DEFAULT_SAMPLE_RATE);
		g_env.scene.work_dims.z = DEFAULT_SAMPLE_RATE;
	}
	if (g_env.scene.maxDistToPrint <= 0)
	{
		printWarning("maxDistToPrint", DEFAULT_MAX_DIST_TO_PRINT);
		g_env.scene.maxDistToPrint = DEFAULT_MAX_DIST_TO_PRINT;
	}
	if (g_env.scene.bounceMax < 1)
	{
		printWarning("bounceMax", DEFAULT_BOUNCE);
		g_env.scene.bounceMax = DEFAULT_BOUNCE;
	}
	return (ret);
}

static int		cameraCheck(void)
{
	int		ret = 1;

	if (!g_env.scene.camera.parsElement[1])
		ret = printError("camera's origin");
	if (g_env.scene.camera.fov <= 0)
	{
		printWarning("fov", DEFAULT_FOV * 180 / M_PI);
		g_env.scene.camera.fov = DEFAULT_FOV;
	}
	return (ret);
}

static t_bbox	objectBboxDefault(t_objType type, float maxDist)
{
	t_bbox		bbox = (t_bbox){
			(cl_float3){{-maxDist, -maxDist, -maxDist}},
			(cl_float3){{maxDist, maxDist, maxDist}}
	};

	if (type == SPHERE)
		bbox = (t_bbox){
			(cl_float3){{-1.f - EPS, -1.f - EPS, -1.f - EPS}},
			(cl_float3){{1.f + EPS, 1.f + EPS, 1.f + EPS}}
		};
	else if (type == DISK)
		bbox = (t_bbox){
			(cl_float3){{-1.f - EPS, -EPS, -1.f - EPS}},
			(cl_float3){{1.f + EPS, EPS, 1.f + EPS}}
			};
	else if (type == PLAN)
		bbox = (t_bbox){
			(cl_float3){{-maxDist, -EPS, -maxDist}},
			(cl_float3){{maxDist, EPS, maxDist}}
			};
	else if (type == CYLINDRE)
		bbox = (t_bbox){
			(cl_float3){{-1.f - EPS, -maxDist, -1.f - EPS}},
			(cl_float3){{1.f + EPS, maxDist, 1.f + EPS}}
			};
	return (bbox);
}

static int		objectCheck(void)
{
	int			ret = 1;
	t_object	*obj;

	for (int i = 0; i < g_env.scene.nbrObject; i++)
	{
		obj = &g_env.scene.object[i];
		if (obj->type == SNONE)
			ret = printError("object's name") * ret;
		if (obj->material == MNONE)
			ret = printError("object's material") * ret;
		if (!obj->parsElement[0])
			ret = printError("object's origin") * ret;
		if (!obj->rotation.x && !obj->rotation.y && !obj->rotation.z)
			obj->isRotated = 0;
		if (!obj->scale.x && !obj->scale.y && !obj->scale.z)
			ret = printError("object's scale") * ret;
		if (!obj->parsElement[9] || !obj->parsElement[10])
			obj->bboxOs = objectBboxDefault(obj->type, g_env.scene.maxDistToPrint);
	}
	return (ret);
}

int		checkElement(void)
{
	return (sceneCheck() * cameraCheck() * objectCheck());
}

int		checkObjectMultiplication(int *object, int currentObject)
{
	int	type[NBR_MEMBER] = {SCENE, CAMERA, OBJECTS};

	for (int i = 0; i < NBR_MEMBER; i++)
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
	else if (!object[2])
		printf("Warning: no object in the file\n");
	return (1);
}
