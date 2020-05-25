#include "rt.h"
#include <math.h>

static cl_float3	calcUpLeftPoint(t_camera cam)
{
	cl_float3		vpUpLeft;
	cl_float3		vx;
	cl_float3		vy;
	cl_float3		vz;

	vz = vec3mul(cam.direction[2], cam.planeDist);
	vy = vec3mul(cam.direction[1], cam.viewPlaneHeight * 0.5);
	vx = vec3mul(cam.direction[0], cam.viewPlaneWidth * 0.5);
	vpUpLeft.x = cam.origin.x + vz.x + vy.x - vx.x;
	vpUpLeft.y = cam.origin.y + vz.y + vy.y - vx.y;
	vpUpLeft.z = cam.origin.z + vz.z + vy.z - vx.z;
	return (vpUpLeft);
}

void				initCamera(t_camera *cam)
{
	cl_float4		rot;

	rot = xyzRotToQuat(cam->rotation);
	cam->direction[2] = vec3d_unit(quatRotWithQuat(clFl3(0, 0, 1), rot));
	cam->direction[0] = vec3d_unit(quatRotWithQuat(clFl3(1, 0, 0), rot));
	cam->direction[1] = vec3d_unit(quatRotWithQuat(clFl3(0, 1, 0), rot));
	cam->planeDist = 1;
	cam->viewPlaneWidth = tan(cam->fov * 0.5) * cam->planeDist * 2 * g_env.scene.work_dims.x * 0.001;
	cam->viewPlaneHeight = tan(cam->fov * 0.5) * cam->planeDist * 2 * g_env.scene.work_dims.y * 0.001;
	cam->vpUpLeft = calcUpLeftPoint(*cam);
	cam->xIndent = cam->viewPlaneWidth / (float)g_env.scene.work_dims.x;
	cam->yIndent = cam->viewPlaneHeight / (float)g_env.scene.work_dims.y;
}
