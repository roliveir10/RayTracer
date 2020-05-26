#include <math.h>
#include "rt.h"

static void			debugPrintVector(cl_float3 v)
{
	printf("[%.1f, %.1f, %.1f]\n", v.x, v.y, v.z);
}

static void			checkPrintVector(char *name, char element, cl_float3 v)
{
	printf("%s", name);
	if (element)
		debugPrintVector(v);
	else
		printf("(null)\n");
}

static void			checkPrintDouble(char *name, char element, double f)
{
	printf("%s", name);
	if (element)
		printf("%1.f\n", f);
	else
		printf("(null)\n");
}

void				debugPrintFile(void)
{
	t_scene			scene;
	t_camera		cam;
	t_object		obj;
	scene = g_env.scene;
	cam = g_env.scene.camera;
	printf("-----SCENE ELEMENT-----\n\n");
	printf("screenX: %d\nscreenY: %d\nsampleRate: %d\nbounceMax: %d\nnbrObject: %d\n",
		scene.work_dims.x, scene.work_dims.y, scene.work_dims.z, scene.bounceMax, scene.nbrObject);
	printf("resolution: %d pixels\n", g_env.resolution);
	printf("ray computed: %ld\n", (long)(g_env.resolution * scene.bounceMax * scene.work_dims.z));
	printf("maxDistToPrint: %.f\n", scene.maxDistToPrint);
	checkPrintVector("background: ", 1, scene.background);
	

	printf("\n----CAMERA ELEMENT----\n\n");
	checkPrintVector("origin: ", 1, cam.origin);
	checkPrintVector("rotation: ", cam.parsElement[2], cam.rotation);
	printf("fov: %.f\n", cam.fov * 180 / M_PI);

	printf("\n----OBJECT ELEMENT----\n\n");

	for (int i = 0; i < g_env.scene.nbrObject; i++)
	{
		obj = g_env.scene.object[i];
		printf("%s:\n", obj.name);
		printf("\t-objType: %d\n", obj.type);
		printf("\t-material: %d\n", obj.material);
		checkPrintVector("\t-origin: ", 1, obj.origin);
		checkPrintVector("\t-color: ", 1, obj.color);
		checkPrintDouble("\t-intensity: ", obj.parsElement[2], obj.intensity);
		checkPrintVector("\t-rotation: ", obj.parsElement[5], obj.rotation);
		printf("\t\t-isRotated: %d\n", (int)obj.isRotated);
		checkPrintVector("\t-scale: ", obj.parsElement[7], obj.scale);
		printf("\t-bboxOs\n");
		printf("\t\t-limitMin: %f %f %f\n\t\t-limitMax: %f %f %f\n", obj.bboxOs.vmin.x, obj.bboxOs.vmin.y,
				obj.bboxOs.vmin.z, obj.bboxOs.vmax.x, obj.bboxOs.vmax.y, obj.bboxOs.vmax.z);
		checkPrintDouble("\t-shininess: ", obj.parsElement[6], obj.shininess);
		checkPrintVector("\t-refrac: ", obj.parsElement[11], obj.refrac);
		checkPrintDouble("\t-opacity: ", obj.parsElement[12], obj.opacity);
		printf("\t-pattern: %d\n", obj.pattern);
		printf("\t-bumpType: %d\n", obj.bump_type);
	}
}
