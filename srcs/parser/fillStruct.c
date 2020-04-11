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

static void			addObjectToStruct(t_env *env, int type)
{
	t_light			*tmpL;
	t_object		*tmpO;

	if (type == LIGHT)
	{
		if (!env->light)
			env->light = ft_memalloc(sizeof(t_light));
		else
		{
			tmpL = env->light;
			while (env->light->next)
				env->light = env->light->next;
			env->light->next = ft_memalloc(sizeof(t_light));
			env->light = tmpL;
		}		
	}
	else if (type == OBJECTS)
	{
		if (!env->object)
			env->object = ft_memalloc(sizeof(t_object));
		else
		{
			tmpO = env->object;
			while (env->object->next)
				env->object = env->object->next;
			env->object->next = ft_memalloc(sizeof(t_object));
			env->object = tmpO;
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
static void			addValueToScene(t_env *env, char *content, int currentName)
{
	if (currentName == AMBIENT)
		env->scene.ambient = atof(content);
	else if (currentName == SPECULAR)
		env->scene.specular = atof(content);
	else
		printf("Warning: invalid member in scene object\n");		
}

static void			addValueToCamera(t_env *env, char *content, int currentName, int vcount)
{
	if (currentName == ORIGIN)
		env->camera.origin = addValueToVector(env->camera.origin, content, vcount);
	else if (currentName == ROTATION)
		env->camera.rotation = addValueToVector(env->camera.rotation, content, vcount);
	else
		printf("Warning: invalid member in camera object\n");		
}

static void			addValueToLight(t_env *env, char *content, int currentName, int vcount)
{
	t_light			*tmp;

	tmp = env->light;
	while (env->light->next)
		env->light = env->light->next;
	if (currentName == ORIGIN)
		env->light->origin = addValueToVector(env->light->origin, content, vcount);
	else if (currentName == COLOR)
		env->light->color = addValueToVector(env->light->color, content, vcount);
	else if (currentName == DIRECTION)
		env->light->direction = addValueToVector(env->light->direction, content, vcount);
	else if (currentName == TYPE)
		env->light->type = ft_strdup(content);
	else
		printf("Warning: invalid member in light object\n");
	env->light = tmp;

}

static void			addValueToObject(t_env *env, char *content, int currentName, int vcount)
{
	t_object		*tmp;

	tmp = env->object;
	while (env->object->next)
		env->object = env->object->next;
	if (currentName == NAME)
		env->object->name = ft_strdup(content);
	else if (currentName == ORIGIN)
		env->object->origin = addValueToVector(env->object->origin, content, vcount);
	else if (currentName == ROTATION)
		env->object->rotation = addValueToVector(env->object->rotation, content, vcount);
	else if (currentName == COLOR)
		env->object->color = addValueToVector(env->object->color, content, vcount);
	else if (currentName == RADIUS)
		env->object->radius = atof(content);
	else if (currentName == ANGLE)
		env->object->angle = atof(content);
	else if (currentName == TEXTURE)
		env->object->texture = ft_strdup(content);
	else if (currentName == TRANSPARENCY)
		env->object->transparency = atof(content);
	else if (currentName == DENSITY)
		env->object->density = atof(content);
	else if (currentName == REFLECTION)
		env->object->reflection = atof(content);
	else
		printf("Warning: invalid member in object object\n");
	env->object = tmp;
}

static void			addValueToStruct(t_env *env, char *content, int currentObject, int currentName, int vcount)
{
	if (currentObject == SCENE)
		addValueToScene(env, content, currentName);
	else if (currentObject == CAMERA)
		addValueToCamera(env, content, currentName, vcount);
	else if (currentObject == LIGHT)
		addValueToLight(env, content, currentName, vcount);
	else if (currentObject == OBJECTS)
		addValueToObject(env, content, currentName, vcount);
}

int				fillStruct(t_env *env, t_ast *ast)
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
			addObjectToStruct(env, ast->type);
			currentObject = ast->type;
		}
		else if (ast->type == -1)
			addObjectToStruct(env, currentObject);
		else if (isStringValue(ast->type) || ast->type == NUMBER)
		{
			addValueToStruct(env, ast->content, currentObject, currentName, vcount);
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
