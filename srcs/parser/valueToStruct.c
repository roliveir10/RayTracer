#include "rt.h"
#include <stdlib.h>
#include <math.h>

t_vector			addValueToVector(t_vector vector, char *content, int vcount)
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

t_vector			addValueToSize(t_vector vector, char *content, int vcount)
{
	t_vector		new;
	double			value;

	new = vector;
	value = atof(content);
	if (vcount == 0)
		new.x = ft_max(value, 0);
	else if (vcount == 1)
		new.y = ft_max(value, 0);
	else if (vcount == 2)
		new.z = ft_max(value, 0);
	if (value <= 0)
		printf("Warning: size value lower or equal to null\n");
	return (new);
}

t_vector			addValueToColor(t_vector vector, char *content, int vcount)
{
	t_vector		new;
	double			color;

	new = vector;
	color = atof(content);
	if (vcount == 0)
		new.x = ft_clamp(color / 255, 0, 1);
	else if (vcount == 1)
		new.y = ft_clamp(color / 255, 0, 1);
	else if (vcount == 2)
	{
		new.z = ft_clamp(color / 255, 0, 1);
		if (!new.x && !new.y && !new.z)
			printf("Warning: color not set or equal to null\n");
	}
	return (new);
}

t_limit				addValueToLimit(t_limit limit, char *content, int vcount)
{
	t_limit			new;
	double			dTmp;

	new = limit;
	dTmp = atof(content);
	if (vcount == 0)
		new.x = dTmp;
	else if (vcount == 1)
		new.y = dTmp;
	else if (vcount == 2)
		new.z = dTmp;
	else if (vcount == 3)
		new.sizeX = ft_max(dTmp, 0);
	else if (vcount == 4)
		new.sizeY = ft_max(dTmp, 0);
	else if (vcount == 5)
		new.sizeZ = ft_max(dTmp, 0);
	if (vcount >= 3 && dTmp < 0)
		printf("Warning: size limit lower than 0. Set by default to %lf", dTmp);
	return (new);
}

int		addValueToStruct(t_ast **ast, int currentObject)
{
	int	ret;

	ret = 1;
	if ((*ast)->type == -1)
		*ast = (*ast)->next;
	while (*ast && ret && (*ast)->type != -1 && !isMemberObject((*ast)->type))
	{
		if (currentObject == SCENE)
			ret = addValueToScene(ast);
		else if (currentObject == CAMERA)
			ret = addValueToCamera(ast);
		else if (currentObject == LIGHT)
			ret = addValueToLight(ast);
		else if (currentObject == OBJECTS)
			ret = addValueToObject(ast);
	}
	return (ret);
}
