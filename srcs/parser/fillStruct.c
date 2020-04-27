#include "rt.h"

static void			mallocObjectToStruct(int type)
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
		}
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

static void			fillExtra(t_object **obj)
{
	t_object		*tmp;

	tmp = *obj;
	while (*obj)
	{
		if ((*obj)->type == BOX)
		{
			(*obj)->b[0].x = -(*obj)->size.x * 0.5;
			(*obj)->b[1].x = (*obj)->size.x * 0.5;
			(*obj)->b[0].y = -(*obj)->size.y * 0.5;
			(*obj)->b[1].y = (*obj)->size.y * 0.5;
			(*obj)->b[0].z = -(*obj)->size.z * 0.5;
			(*obj)->b[1].z = (*obj)->size.z * 0.5;
		}
		*obj = (*obj)->next;
	}
	*obj = tmp;
}

int				fillStruct(t_ast *ast)
{
	int			currentObject = 0;
	int			object[NBR_OBJECT];

	ft_bzero(&object, sizeof(int) * NBR_OBJECT);
	while (ast)
	{
		if (isMemberObject(ast->type))
		{
			currentObject = ast->type;
			if (!checkObjectMultiplication(object, currentObject))
				return (0);
			ast = ast->next;
		}
		if (ast)
		{
			if (currentObject == LIGHT || currentObject == OBJECTS)
				mallocObjectToStruct(currentObject);
			if (!addValueFromMember(&ast, currentObject))
				return (0);
		}
	}
	fillExtra(&g_env.object);
	return (checkObject(object));
}
