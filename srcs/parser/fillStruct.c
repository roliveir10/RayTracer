#include "rt.h"
#include <stdlib.h>

static void			incrementElement(int type, t_nbrElement *nbrElement)
{
	switch (type)
	{
		case (CAMERA):
			nbrElement->camera++;
			break ;
		case (SCENE):
			nbrElement->scene++;
			break ;
		case (LIGHT):
			nbrElement->light++;
			break ;
		case (OBJECTS):
			nbrElement->object++;
			break ;
	}
}

static void			countElement(t_ast *ast, t_nbrElement *nbrElement)
{
	int			currentElement = 0;

	while (ast)
	{
		if (isMemberObject(ast->type))
		{
			incrementElement(ast->type, nbrElement);
			currentElement = ast->type;
		}
		else if (ast->type == -1)
			incrementElement(currentElement, nbrElement);
		ast = ast->next;
	}
}

static int			elementValidity(t_nbrElement elements)
{
	int			valid;

	valid = 1;
	if (elements.scene > 1)
	{
		dprintf(2, "too many scene objects : 1 permitted, %d in the file. Aborting...\n", elements.scene);
		valid = 0;
	}	
	if (elements.camera > 1)
	{
		dprintf(2, "too many camera objects : 1 permitted, %d in the file. Aborting... \n", elements.camera);
		valid = 0;
	}
	else if (elements.camera < 1)
	{
		dprintf(2, "camera object is missing. Aborting...\n");
		valid = 0;
	}
	if (elements.light < 1)
		printf("Warning: no light in the scene\n");
	if (elements.object < 1)
		printf("Warning: no object in the scene\n");
	return (valid);
}

static void			addObjectToStruct(int type)
{
	t_light			*tmpL;
	t_object		*tmpO;

	if (type == LIGHT)
	{
		if (!g_env.light)
			g_env.light = ft_memalloc(sizeof(t_light));
		else
		{
			tmpL = g_env.light;
			while (g_env.light->next)
				g_env.light = g_env.light->next;
			g_env.light->next = ft_memalloc(sizeof(t_light));
			g_env.light = tmpL;
		}		
	}
	else if (type == OBJECTS)
	{
		if (!g_env.object)
			g_env.object = ft_memalloc(sizeof(t_object));
		else
		{
			tmpO = g_env.object;
			while (g_env.object->next)
				g_env.object = g_env.object->next;
			g_env.object->next = ft_memalloc(sizeof(t_object));
			g_env.object = tmpO;
		}
	}
}

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
	t_object		*tmp;

	tmp = g_env.object;
	while (g_env.object->next)
		g_env.object = g_env.object->next;
	if (currentName == NAME)
		g_env.object->name = ft_strdup(content);
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

static void			addValueToStruct(char *content, int currentObject, int currentName, int vcount)
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

int				fillStruct(t_ast *ast)
{
	int			currentObject = 0;
	int			currentName = 0;
	t_nbrElement		elements;
	int			vcount;

	ft_bzero(&elements, sizeof(t_nbrElement));
	countElement(ast, &elements);
	if (!elementValidity(elements))
		return (0);
	while (ast)
	{
		if (isMemberObject(ast->type))
		{
			addObjectToStruct(ast->type);
			currentObject = ast->type;
		}
		else if (ast->type == -1)
			addObjectToStruct(currentObject);
		else if (isStringValue(ast->type) || ast->type == NUMBER)
		{
			addValueToStruct(ast->content, currentObject, currentName, vcount);
			vcount++;
		}
		else
		{
			vcount = 0;
			currentName = ast->type;
		}
		ast = ast->next;
	}
	return (1);
}
