static t_intersection		primitiveIntersection
(
	float					*new_t,
	t_ray					*rayOs,
	t_objType				type,
	t_bbox					aabb
)
{
	t_intersection			inter;

	if (type == SPHERE)
		inter = sphere(new_t, rayOs, aabb);
	else if (type == PLAN)
		inter = plan(new_t, rayOs);
	else if (type == CYLINDRE)
		inter = cylindre(new_t, rayOs);
	else
		inter = NONE;
	return (inter);
}

/*{
	if (obj->type == SPHERE)
		return (sphere(obj, ray));
	else if (obj->type == PLAN)
		return (plan(obj, ray));
	else if (obj->type == CYLINDRE)
		return (cylindre(obj, ray));
	else if (obj->type == CONE)
		return (cone(obj, ray));
	else if (obj->type == BOX)
		return (box(obj, ray));
	else if (obj->type == DISK)
		return (disk(obj, ray));
	else if (obj->type == HYPERBOLOID)
		return (hyperboloid(obj, ray));
	return (-1.f);
}*/

static t_intersection	intersectScene
(
	__constant t_scene	*scene,
	t_ray				*ray
)
{
	__constant t_object	*obj;
	t_intersection		inter;
	float				tmax;
	float				new_t;
	t_ray				rayOs;
	t_ray				finalRayOs;

	tmax = ray->t;
	inter = NONE;
	for (int i = 0; i < scene->nbrObject; i++)
	{
		obj = &scene->object[i];
		rayOs = *ray;
		rayOs.o = applyHomogeneousMatrice(obj->w_to_o, rayOs.o);
		rayOs.dir = applyLinearMatrice(obj->w_to_o, rayOs.dir);
		rayOs.interType = primitiveIntersection(&new_t, &rayOs, obj->type, obj->bboxOs);
		if (rayOs.interType && EPSILON < new_t && new_t < ray->t)
		{
			rayOs.hitPos = rayOs.o + new_t * rayOs.dir;
			if (hitPosInBbox(rayOs.hitPos, obj->bboxOs))
			{
				inter = rayOs.interType;
				finalRayOs = rayOs;
				finalRayOs.objId = i;
				ray->t = new_t;
				finalRayOs.t = new_t;
			}
		}
	}
	if (inter)
		*ray = finalRayOs;
	return (inter);
}

static t_ray		globalIllum
(
					__constant t_scene		*scene,
					uint2					*random_seeds,
					t_ray					*ray
)
{
	__constant t_object		*obj = &scene->object[ray->objId];
	t_ray					newRay;
	float3					hitPos;
	float3					normal;
	t_texture				texture;
	bool					isInterInside;

	hitPos = ray->hitPos;
	normal = ray->interType * primitiveNormal(hitPos, obj->type);
	isInterInside = (ray->interType == INSIDE);

	texture = textureProperties(scene, obj, normal);
	normal = texture.bump_normal;

	newRay.refrac = ray->refrac;
	newRay.objId = -1;
	newRay.interType = NONE;
	newRay.t = scene->maxDistToPrint;
	newRay.complete = (obj->material == MLIGHT);
	newRay.lum_acc = ray->lum_acc;

	if (newRay.complete)
	{
		newRay.lum_acc += ray->lum_mask * texture.rgb * obj->intensity;
		return (newRay);
	}
	else if (obj->material == MDIFFUSE)
	{
		newRay.dir = randDirCoshemi(random_seeds, normal);
		newRay.lum_mask = ray->lum_mask * texture.rgb * (float3)(dot(normal, newRay.dir));
	}

	hitPos = EPSILON * normal + hitPos;
	newRay.o = applyHomogeneousMatrice(obj->o_to_w, hitPos);
	newRay.dir = applyLinearMatrice(obj->o_to_w, newRay.dir);
	return (newRay);
}

static t_ray			createCamRay(__constant t_scene *scene, uint2 * random_seeds)
{
	int const			x_coord = get_global_id(0);
	int const			y_coord = get_global_id(1);
	t_ray				camRay;
	float3				pixelPos;
	float				x = x_coord + frand0To1(random_seeds);
	float				y = y_coord + frand0To1(random_seeds);

	camRay.t = scene->maxDistToPrint;
	camRay.objId = -1;
	camRay.hitPos = (float3)(0.f);
	camRay.lum_mask = (float3)(1.f);
	camRay.lum_acc = (float3)(0.f);
	camRay.refrac = 1.f;
	camRay.interType = NONE;
	camRay.complete = false;
	camRay.o = scene->camera.origin;

	pixelPos = (scene->camera.direction[0] * x * scene->camera.xIndent + scene->camera.vpUpLeft) - (scene->camera.direction[1] * y * scene->camera.yIndent);
	camRay.dir = normalize(pixelPos - camRay.o);
	return (camRay);
}

static float3		getPixColor
(
	__constant t_scene	*scene,
	uint2				*random_seeds
)
{
	t_ray			ray_i;
	t_intersection	inter;

	ray_i = createCamRay(scene, random_seeds);
	for (int bounces = 0; !ray_i.complete && bounces < scene->bounceMax; bounces++)
	{
		inter = intersectScene(scene, &ray_i);
		if (inter)
			ray_i = globalIllum(scene, random_seeds, &ray_i);
		else
		{
			ray_i.complete = true;
			ray_i.lum_acc += ray_i.lum_mask * scene->background;
		}
	}
	return (ray_i.lum_acc);
}

__kernel void		pixelColorMain
(
					__global float3 * ray,
					__constant t_scene * scene
)
{
	int const		x_id = get_global_id(0);
	int	const		y_id = get_global_id(1);
	size_t const	block_x_id = x_id - get_global_offset(0);
	size_t const	block_y_id = y_id - get_global_offset(1);
	int const		ray_id = get_global_id(2);

	if (x_id >= scene->work_dims.x || y_id >= scene->work_dims.y || ray_id >= scene->work_dims.z)
		return ;

	size_t const	block_width = get_global_size(0);
	size_t const	block_height = get_global_size(1);
	size_t const	work_item_id = block_height * block_width * ray_id
			+ block_width * block_y_id + block_x_id;

	uint2			random_seeds;
	float3			lum_acc;

	random_seeds.x = x_id ^ ray_id + y_id;
	random_seeds.y = y_id ^ ray_id + x_id * ray_id;

	getRand(&random_seeds);

	lum_acc = getPixColor(scene, &random_seeds);

	ray[work_item_id] = lum_acc;
}

__kernel void		pixAverage
(
					__global uint * output,
					__global float3	* ray,
					__constant uint8 * global_dims
)
{
	uint3 const		work_steps = global_dims->s012;
	uint3 const		work_dims = global_dims->s456;

	uint const		x_id = get_global_id(0);
	uint const		y_id = get_global_id(1);

	if (x_id >= work_dims.x || y_id >= work_dims.y)
		return ;

	size_t const	block_x_id = x_id - get_global_offset(0);
	size_t const	block_y_id = y_id - get_global_offset(1);
	size_t const	work_item_id = work_dims.x * y_id + x_id;
	size_t const	init = get_global_size(0) * block_y_id + block_x_id;
	size_t const	inc = work_steps.y * work_steps.x;
	int const		size = inc * work_dims.z;
	float const		inv_samp_size = native_recip((float)work_dims.z);
	float3			vcolor3 = (float3)(0.f);
	uchar3			color3;
	uint			color;

	#pragma unroll
	for (int i = init; i < size; i += inc)
	{
		vcolor3 += ray[i];
	}
	
	vcolor3 *= (float3)(inv_samp_size);
	color3.x = (uchar)(clamp(pow(vcolor3.x, .45f), 0.f, 1.f) * 255.f);
	color3.y = (uchar)(clamp(pow(vcolor3.y, .45f), 0.f, 1.f) * 255.f);
	color3.z = (uchar)(clamp(pow(vcolor3.z, .45f), 0.f, 1.f) * 255.f);
	color = 0xFF000000 | (color3.x << 16) | (color3.y << 8) | (color3.z);
	output[work_item_id] = color;
}
