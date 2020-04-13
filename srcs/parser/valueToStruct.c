#include "rt.h"
#include <stdlib.h>

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
static void			addValueToScene(char *content, int currentName)
{
		if (currentName == AMBIENT)
				g_env.scene.ambient = atof(content);
		else if (currentName == SPECULAR)
				g_env.scene.specular = atof(content);
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
		t_light			*tmp;

		tmp = g_env.light;
		while (g_env.light->next)
				g_env.light = g_env.light->next;
		if (currentName == ORIGIN)
				g_env.light->origin = addValueToVector(g_env.light->origin, content, vcount);
		else if (currentName == COLOR)
				g_env.light->color = addValueToVector(g_env.light->color, content, vcount);
		else if (currentName == DIRECTION)
				g_env.light->direction = addValueToVector(g_env.light->direction, content, vcount);
		else if (currentName == TYPE)
				g_env.light->type = ft_strdup(content);
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
				g_env.object->color = addValueToVector(g_env.object->color, content, vcount);
		else if (currentName == RADIUS)
				g_env.object->radius = atof(content);
		else if (currentName == ANGLE)
				g_env.object->angle = atof(content);
		else if (currentName == TEXTURE)
				g_env.object->texture = ft_strdup(content);
		else if (currentName == TRANSPARENCY)
				g_env.object->transparency = atof(content);
		else if (currentName == DENSITY)
				g_env.object->density = atof(content);
		else if (currentName == REFLECTION)
				g_env.object->reflection = atof(content);
		else
				printf("Warning: invalid member in object object\n");
		g_env.object = tmp;
}

void			addValueToStruct(char *content, int currentObject, int currentName, int vcount)
{
		if (currentObject == SCENE)
				addValueToScene(content, currentName);
		else if (currentObject == CAMERA)
				addValueToCamera(content, currentName, vcount);
		else if (currentObject == LIGHT)
				addValueToLight(content, currentName, vcount);
		else if (currentObject == OBJECTS)
				addValueToObject(content, currentName, vcount);
}
