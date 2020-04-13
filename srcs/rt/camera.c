#include "rt.h"

static t_vector		calcUpLeftPoint(t_camera cam, int height, int width)
{
	t_vector		vpUpLeft;
	
	vpUpLeft = ft_vadd(cam.origin, ft_vmul(cam.direction[2], FOV));
	vpUpLeft = ft_vadd(vpUpLeft, ft_vmul(cam.direction[1], height * 0.5));
	vpUpLeft = ft_vsub(ft_vmul(cam.direction[0], width * 0.5), vpUpLeft);
	return (vpUpLeft);
}

void				initCamera(t_camera *cam)
{
	cam->direction[0].x = 1.0;
	cam->direction[1].y = 1.0;
	cam->direction[2].z = 1.0;
	cam->vpUpLeft = calcUpLeftPoint(*cam, VIEW_PLANE_HEIGHT, VIEW_PLANE_WIDTH);
}
