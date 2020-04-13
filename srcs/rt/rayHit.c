#include "rt.h"

t_vector			vDirCamToPoint(t_camera cam, double x, double y)
{
	t_vector		vDir;
	double			xIndent;
	double			yIndent;

	xIndent = (double)VIEW_PLANE_WIDTH / SCREENX;
	yIndent = (double)VIEW_PLANE_HEIGHT / SCREENY;
	vDir = ft_vsub(ft_vmul(cam.direction[1], yIndent * y),
				ft_vadd(cam.vpUpLeft, ft_vmul(cam.direction[0], xIndent * x)));
	return (ft_normalize(vDir));
}

t_rayHit			rayCast(t_vector o, t_vector dir, double maxDist)
{
	t_rayHit		hit;
	t_object		*currentObj;

	ft_bzero(&hit, sizeof(t_rayHit));
	currentObj = g_env.object;
	while (currentObj)
	{
		currentObj = currentObj->next;
	}
	(void)o;
	(void)dir;
	(void)maxDist;
	return (hit);
}
