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

	debugPrintObject(obj);
}
