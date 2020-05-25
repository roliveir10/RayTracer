#include "rt.h"

static void			initScene(void)
{
	int				renderDist = g_env.scene.maxDistToPrint;

	g_env.resolution = g_env.scene.work_dims.x * g_env.scene.work_dims.y;
	g_env.scene.bboxWs.vmin = (cl_float3){{-renderDist, -renderDist, -renderDist}};
	g_env.scene.bboxWs.vmax = (cl_float3){{renderDist, renderDist, renderDist}};
}

int				fillStruct(t_ast *ast)
{
	int			currentObject = 0;
	int			member[NBR_MEMBER];

	ft_bzero(&member, sizeof(int) * NBR_MEMBER);
	while (ast)
	{
		if (isMemberObject(ast->type))
		{
			currentObject = ast->type;
			if (!checkObjectMultiplication(member, currentObject))
				return (0);
			ast = ast->next;
		}
		if (ast)
		{
			if (!addValueFromMember(&ast, currentObject))
				return (0);
			if (currentObject == OBJECTS)
				g_env.scene.nbrObject++;
		}
	}
	initScene();
	if (!checkObject(member))
		return (0);
	return (checkElement());
}
