#include "rt.h"

static t_vector		calcUpLeftPoint(t_camera cam)
{
	t_vector		vpUpLeft;
	t_vector		vx;
	t_vector		vy;
	t_vector		vz;

	vz = ft_vmul(cam.direction[2], g_env.camera.fov);
	vy = ft_vmul(cam.direction[1], g_env.scene.screenY * 0.005);
	vx = ft_vmul(cam.direction[0], g_env.scene.screenX * 0.005);
	vpUpLeft.x = cam.origin.x + vz.x + vy.x - vx.x;
	vpUpLeft.y = cam.origin.y + vz.y + vy.y - vx.y;
	vpUpLeft.z = cam.origin.z + vz.z + vy.z - vx.z;
	return (vpUpLeft);
}

void				initCamera(t_camera *cam)
{
	cam->vpUpLeft = calcUpLeftPoint(*cam);
}
