static void				getBboxVertices(float3 * vertices, t_bbox aabb)
{
	vertices[0] = (float3)(aabb.vmin.x, aabb.vmin.y, aabb.vmin.z);
	vertices[1] = (float3)(aabb.vmin.x, aabb.vmin.y, aabb.vmax.z);
	vertices[2] = (float3)(aabb.vmin.x, aabb.vmax.y, aabb.vmin.z);
	vertices[3] = (float3)(aabb.vmin.x, aabb.vmax.y, aabb.vmax.z);
	vertices[4] = (float3)(aabb.vmax.x, aabb.vmin.y, aabb.vmin.z);
	vertices[5] = (float3)(aabb.vmax.x, aabb.vmin.y, aabb.vmax.z);
	vertices[6] = (float3)(aabb.vmax.x, aabb.vmax.y, aabb.vmin.z);
	vertices[7] = (float3)(aabb.vmax.x, aabb.vmax.y, aabb.vmax.z);
}

static t_bbox			buildObjectBbox(__global t_object *obj)
{
	float3				osBboxVertices[8];
	t_bbox				result;

	getBboxVertices(osBboxVertices, obj->bboxOs);
	for (int i = 0; i < 8; i++)
		osBboxVertices[i] = applyHomogeneousMatrice(obj->o_to_w, osBboxVertices[i]);
	result.vmax = result.vmin = osBboxVertices[0];
	for (int i = 1; i < 8; i++)
	{
		result.vmin = fmin(result.vmin, osBboxVertices[i]);
		result.vmax = fmax(result.vmax, osBboxVertices[i]);
	}
	return (result);
}

static void				buildObjectMatrices(__global t_object *obj)
{
	float3				pos = obj->origin;
	float3				scale = obj->scale;
	float3				rot = obj->rotation;
	float16				rotMat;
	float16				tmpMat;

	rotMat = buildRotationMat33in44(rot.x, 0);
	tmpMat = buildRotationMat33in44(rot.y, 1);
	rotMat = mat44Mul(tmpMat, rotMat);
	tmpMat = buildRotationMat33in44(rot.z, 2);
	rotMat = mat44Mul(tmpMat, rotMat);
	tmpMat = buildDiagonalMat33in44(scale);
	obj->o_to_w = mat44Mul(rotMat, tmpMat);
	obj->o_to_w.sCDE = pos;
	tmpMat = mat33in44Inv(obj->o_to_w);
	obj->w_to_o = tmpMat;
	obj->w_to_o.sCDE = applyLinearMatrice(tmpMat, -pos);
	obj->n_to_w = mat44Transpose(tmpMat);
}

__kernel void			initScene(__global t_scene *scene)
{
	int const			obj_id = get_global_id(0);
	__global t_object*	obj = &scene->object[obj_id];
	
	buildObjectMatrices(obj);
//	obj->bboxWs = buildObjectBbox(obj);

	debugPrintObject(obj);
}
