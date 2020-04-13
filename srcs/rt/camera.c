#include "rt.h"

static t_vector		calcUpLeftPoint(t_camera cam)
{
	t_vector		vpUpLeft;
	t_vector		vx;
	t_vector		vy;
	t_vector		vz;

	vz = ft_vmul(cam.direction[2], 1.0);
	vy = ft_vmul(cam.direction[1], 1.0 * 0.5);
	vx = ft_vmul(cam.direction[0], 1.0 * 0.5);
	vpUpLeft.x = cam.origin.x + vz.x + vy.x - vx.x;
	vpUpLeft.y = cam.origin.y + vz.y + vy.y - vx.y;
	vpUpLeft.z = cam.origin.z + vz.z + vy.z - vx.z;
	return (vpUpLeft);
}

void				initCamera(t_camera *cam)
{
	cam->direction[0].x = 1.0;
	cam->direction[1].y = 1.0;
	cam->direction[2].z = 1.0;
	cam->vpUpLeft = calcUpLeftPoint(*cam);
}
