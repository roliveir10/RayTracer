#include "rt.h"

static void		parsOrigin(t_ast **ast)
{
	for (int i = 0; i < 3; i++)
	{
		g_env.camera.origin = addValueToVector(g_env.camera.origin, (*ast)->content, i);
		*ast = (*ast)->next;
	}
}

static void		parsRotation(t_ast **ast)
{
	for (int i = 0; i < 3; i++)
	{
		g_env.camera.rotation = addValueToVector(g_env.camera.rotation, (*ast)->content, i);
		*ast = (*ast)->next;
	}
}
static void		fillCamera(int currentField, int *element, t_ast **ast)
{
	t_wordType	word[CAMERA_ELEMENT] = {
		{"\"origin\"", ORIGIN},
		{"\"rotation\"", ROTATION}
	};

	if (currentField == ORIGIN)
		parsOrigin(ast);
	else if (currentField == ROTATION)
		parsRotation(ast);
	else
		printf("Warning: invalid field in camera object\n");
	for (int i = 0; i < CAMERA_ELEMENT; i++)
		if (word[i].type == currentField)
		{
			element[i] = 1;
			break ;
		}
}

static int		checkElement(int *element)
{
	if (element[0] == 1)
		return (1);
	dprintf(2, "Error: origin not set for camera object. Aborting...\n");
	return (0);
}

int			addValueToCamera(t_ast **ast)
{
	int		element[CAMERA_ELEMENT];
	int		currentField;

	ft_bzero(&element, sizeof(int) * CAMERA_ELEMENT);
	while (*ast && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if ((*ast)->type == NUMBER || isStringValue((*ast)->type))
		{
			fillCamera(currentField, element, ast);
			if (!isMemberVector(currentField))
				*ast = (*ast)->next;
		}
		else
		{
			currentField = (*ast)->type;
			*ast = (*ast)->next;
		}
	}
	return (checkElement(element));
}
