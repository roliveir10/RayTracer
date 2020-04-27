#include "rt.h"
#include <math.h>

static t_vector		calcUpLeftPoint(t_camera cam)
{
	t_vector		vpUpLeft;
	t_vector		vx;
	t_vector		vy;
	t_vector		vz;

	vz = ft_vmul(cam.direction[2], cam.planeDist);
	vy = ft_vmul(cam.direction[1], cam.viewPlaneHeight * 0.5);
	vx = ft_vmul(cam.direction[0], cam.viewPlaneWidth * 0.5);
	vpUpLeft.x = cam.origin.x + vz.x + vy.x - vx.x;
	vpUpLeft.y = cam.origin.y + vz.y + vy.y - vx.y;
	vpUpLeft.z = cam.origin.z + vz.z + vy.z - vx.z;
	return (vpUpLeft);
}

void				initCamera(t_camera *cam)
{
	cam->planeDist = 1;
	cam->viewPlaneWidth = tan(cam->fov * 0.5 * M_PI / 180) * cam->planeDist * 2 * g_env.scene.screenX * 0.001;
	cam->viewPlaneHeight = tan(cam->fov * 0.5 * M_PI / 180) * cam->planeDist * 2 * g_env.scene.screenY * 0.001;
	cam->vpUpLeft = calcUpLeftPoint(*cam);
}
