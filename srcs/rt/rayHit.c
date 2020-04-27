#include "rt.h"

t_vector			vDirCamToPoint(t_camera cam, double x, double y)
{
	t_vector		pointOnCanvas;
	t_vector		vDir;
	double			xIndent;
	double			yIndent;

	xIndent = cam.viewPlaneWidth / (double)g_env.scene.screenX;
	yIndent = cam.viewPlaneHeight / (double)g_env.scene.screenY;
	pointOnCanvas = ft_vsub(ft_vmul(cam.direction[1], y * yIndent),
				ft_vadd(cam.vpUpLeft, ft_vmul(cam.direction[0], x * xIndent)));
	vDir = ft_vsub(cam.origin, pointOnCanvas);
	return (ft_normalize(vDir));
}

double				distToHit(t_object obj, t_ray ray)
{
	double			(*func[NBR_SHAPE])(t_object, t_ray) = {
		sphere, plan, cylindre, cone, box};
	
	return (func[obj.type](obj, ray));
}

static void			addClosestObj(t_rayHit *hit, t_object obj, double dist, double maxDist)
{
	if (dist <= 0 || dist >= maxDist)
		return ;
	if (dist > 0 && (!hit->distance || dist < hit->distance))
	{
		hit->distance = dist;
		hit->obj = obj;
	}
}

t_vector			hitPoint(t_ray ray, double dist)
{
	return (ft_vadd(ray.o, ft_vmul(ray.dir, dist)));
}

static void			getHitData(t_rayHit *hit, t_ray ray)
{
	double			invNormal;

	if (!hit->distance)
	{
		hit->color = g_env.scene.background;
		return;
	}
	hit->viewDir = ft_vmul(ray.dir, -1);
	hit->point = hitPoint(ray, hit->distance);
	hit->normal = normal(*hit);
	for (int i = 2; i >= 0; i--)
		hit->normal = ft_vrotate(hit->normal, hit->obj.matRotInv[i]);
	invNormal = ft_dot(hit->normal, ray.dir);
	if (invNormal > 0)
		hit->normal = ft_vmul(hit->normal, -1);
	hit->point = ft_vadd(ft_vmul(hit->normal, 1e-5), hit->point);
}

t_rayHit			rayCast(t_ray ray, double maxDist)
{
	t_rayHit		hit;
	t_object		*currentObj;
	double			currentDist;

	ft_bzero(&hit, sizeof(t_rayHit));
	currentObj = g_env.object;
	while (currentObj)
	{
		currentDist = distToHit(*currentObj, ray);
		addClosestObj(&hit, *currentObj, currentDist, maxDist);
		currentObj = currentObj->next;
	}
	getHitData(&hit, ray);
	return (hit);
}
