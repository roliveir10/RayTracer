#include "rt.h"

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
		{
			g_env.object = ft_memalloc(sizeof(t_object));
			g_env.object->type = -1;
		}
		else
		{
			tmpO = g_env.object;
			while (g_env.object->next)
				g_env.object = g_env.object->next;
			g_env.object->next = ft_memalloc(sizeof(t_object));
			g_env.object->next->type = -1;
			g_env.object = tmpO;
		}
	}
}

static void		addDefaultValue(void)
{
	if (!g_env.scene.screenX || !g_env.scene.screenY)
	{
		g_env.scene.screenX = 1400;
		g_env.scene.screenY = 900;
		printf("Warning: `screenX` set by default to 1400. `screenY` set by default to 900\n");
	}
	if (!g_env.camera.fov)
	{
		g_env.camera.fov = 10;
		printf("Warning: `fov` set by default to 10\n");
	}
	if (!g_env.scene.sampleRate)
	{
		g_env.scene.sampleRate = 1;
		printf("Warning: `sampleRate` set by default to 1\n");
	}
	if (!g_env.scene.pixPerUnit)
	{
		g_env.scene.pixPerUnit = 1;
		printf("Warning: `pixPerUnit` set by default to 1\n");
	}
	if (!g_env.scene.maxDistToPrint)
	{
		g_env.scene.maxDistToPrint = 15000;
		printf("Warning: `maxDistToPrint` set by default to 15000\n");
	}
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
	addDefaultValue();
	return (1);
}
