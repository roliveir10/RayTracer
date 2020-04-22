#include "rt.h"

int				objectValidity(t_nbrObject objects)
{
	int			valid;

	valid = 1;
	if (objects.scene > 1)
	{
		dprintf(2, "too many scene objects : 1 permitted, %d in the file. Aborting...\n", objects.scene);
		valid = 0;
	}
	if (objects.camera > 1)
	{
		dprintf(2, "too many camera objects : 1 permitted, %d in the file. Aborting... \n", objects.camera);
		valid = 0;
	}
	else if (objects.camera < 1)
	{
		dprintf(2, "camera object is missing. Aborting...\n");
		valid = 0;
	}
	if (objects.light < 1)
		printf("Warning: no light in the scene\n");
	if (objects.object < 1)
		printf("Warning: no object in the scene\n");
	return (valid);
}

static void			incrementObject(int type, t_nbrObject *nbrObject)
{
	switch (type)
	{
		case (CAMERA):
			nbrObject->camera++;
			break ;
		case (SCENE):
			nbrObject->scene++;
			break ;
		case (LIGHT):
			nbrObject->light++;
			break ;
		case (OBJECTS):
			nbrObject->object++;
			break ;
	}
}

void				countObject(t_ast *ast, t_nbrObject *nbrObject)
{
	int			currentObject = 0;

	while (ast)
	{
		if (isMemberObject(ast->type))
		{
			incrementObject(ast->type, nbrObject);
			currentObject = ast->type;
		}
		else if (ast->type == -1)
			incrementObject(currentObject, nbrObject);
		ast = ast->next;
	}
}
