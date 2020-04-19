#include "rt.h"
#include <stdlib.h>
#include <math.h>

static t_vector			addValueToVector(t_vector vector, char *content, int vcount)
{
		t_vector		new;

		new = vector;
		if (vcount == 0)
				new.x = atof(content);
		else if (vcount == 1)
				new.y = atof(content);
		else if (vcount == 2)
				new.z = atof(content);
		return (new);
}

static t_vector		addValueToColor(t_vector vector, char *content, int vcount)
{
	t_vector		new;

	new = vector;
	if (vcount == 0)
		new.x = ft_clamp(atof(content) / 255, 0, 1);
	else if (vcount == 1)
		new.y = ft_clamp(atof(content) / 255, 0, 1);
	else if (vcount == 2)
		new.z = ft_clamp(atof(content) / 255, 0, 1);
	return (new);
}

static void			addValueToScene(char *content, int currentName, int vcount)
{
		if (currentName == AMBIENT)
				g_env.scene.ambient = atof(content);
		else if (currentName == SPECULAR)
				g_env.scene.specular = atof(content);
		else if (currentName == BACKGROUND)
				g_env.scene.background = addValueToColor(g_env.scene.background, content, vcount);
		else if (currentName == SCREENX)
				g_env.scene.screenX = ft_atoi(content);
		else if (currentName == SCREENY)
				g_env.scene.screenY = ft_atoi(content);
		else if (currentName == FOV)
				g_env.camera.fov = ft_atoi(content);
		else if (currentName == SAMPLERATE)
				g_env.scene.sampleRate = ft_atoi(content);
		else if (currentName == PIXPERUNIT)
				g_env.scene.pixPerUnit = ft_atoi(content);
		else if (currentName == MAXDISTTOPRINT)
				g_env.scene.maxDistToPrint = ft_atoi(content);
		else
				printf("Warning: invalid member in scene object\n");
}

static void			addValueToCamera(char *content, int currentName, int vcount)
{
		if (currentName == ORIGIN)
				g_env.camera.origin = addValueToVector(g_env.camera.origin, content, vcount);
		else if (currentName == ROTATION)
				g_env.camera.rotation = addValueToVector(g_env.camera.rotation, content, vcount);
		else
				printf("Warning: invalid member in camera object\n");
}

static void			addValueToLight(char *content, int currentName, int vcount)
{
		const int		type[NBR_LIGHT_TYPE] = {POINTL, DIRECTIONAL, SPOT};
		const char		*typeString[NBR_LIGHT_TYPE] = {"\"point\"", "\"directional\"", "\"spot\""};
		t_light			*tmp;

		tmp = g_env.light;
		while (g_env.light->next)
				g_env.light = g_env.light->next;
		if (currentName == ORIGIN)
				g_env.light->origin = addValueToVector(g_env.light->origin, content, vcount);
		else if (currentName == COLOR)
				g_env.light->color = addValueToColor(g_env.light->color, content, vcount);
		else if (currentName == TYPE)
		{
				g_env.light->type = ft_strdup(content);
				for (int i = 0; i < NBR_LIGHT_TYPE; i++)
					if (!ft_strcmp(g_env.light->type, typeString[i]))
						g_env.light->etype = type[i];
		}
		else
				printf("Warning: invalid member in light object\n");
		g_env.light = tmp;

}

static void			addValueToObject(char *content, int currentName, int vcount)
{
		const int		type[NBR_SHAPE] = {SPHERE, PLAN, CYLINDRE, CONE};
		const char		*typeString[NBR_SHAPE] = {"\"sphere\"", "\"plan\"", "\"cylindre\"", "\"cone\""};
		t_object		*tmp;

		tmp = g_env.object;
		while (g_env.object->next)
				g_env.object = g_env.object->next;
		if (currentName == NAME)
		{
				g_env.object->name = ft_strdup(content);
				for (int i = 0; i < NBR_SHAPE; i++)
						if (!ft_strcmp(g_env.object->name, typeString[i]))
								g_env.object->type = type[i];
		}
		else if (currentName == ORIGIN)
				g_env.object->origin = addValueToVector(g_env.object->origin, content, vcount);
		else if (currentName == ROTATION)
				g_env.object->rotation = addValueToVector(g_env.object->rotation, content, vcount);
		else if (currentName == COLOR)
				g_env.object->color = addValueToColor(g_env.object->color, content, vcount);
		else if (currentName == RADIUS)
				g_env.object->radius = atof(content);
		else if (currentName == ANGLE)
				g_env.object->angle = atof(content) * M_PI / 180;
		else if (currentName == TEXTURE)
				g_env.object->texture = ft_strdup(content);
		else if (currentName == TRANSPARENCY)
				g_env.object->transparency = atof(content);
		else if (currentName == DENSITY)
				g_env.object->density = atof(content);
		else if (currentName == REFLECTION)
				g_env.object->reflection = atof(content);
		else if (currentName == SHININESS)
				g_env.object->shininess = atof(content);
		else if (currentName == SHININESSSTRENGTH)
				g_env.object->shininessStrength = atof(content);
		else
				printf("Warning: invalid member in object object\n");
		g_env.object = tmp;
}

void			addValueToStruct(char *content, int currentObject, int currentName, int vcount)
{
		if (currentObject == SCENE)
				addValueToScene(content, currentName, vcount);
		else if (currentObject == CAMERA)
				addValueToCamera(content, currentName, vcount);
		else if (currentObject == LIGHT)
				addValueToLight(content, currentName, vcount);
		else if (currentObject == OBJECTS)
				addValueToObject(content, currentName, vcount);
}
