static float3				sphereNormal(const float3 hitPoint)
{
	return (hitPoint);
}

static float3				planNormal(void)
{
	return ((float3)(0.f, 1.f, 0.f));
}

/*static float3				diskNormal(void)
{
	return ((float3)(0.f, 1.f, 0.f));
}*/

static float3				cylindreNormal(float3 hitPoint)
{
	return ((float3)(hitPoint.x, 0.f, hitPoint.z));
}
/*
static float3				coneNormal(const float3 hitPoint, const float angle)
{
	float3					normal;
	float					neg;
	float					tanAngle;
	float3					point;

	point = hitPoint;
	neg = point.y <= 0.f ? 1.f : -1.f;
	tanAngle = tan(angle * .5f) * neg;
	normal = normalize(point);
	normal.x /= tanAngle;
	normal.y = tanAngle;
	normal.z /= tanAngle;
	return (normalize(normal));
}

static float3				boxNormal(const t_object obj, const float3 hitPoint)
{
	float3			normal = (float3)(0.f);

	if (hitPoint.z < obj.bbox[0].z + EPSILON)
		normal.z = -1.f;
	else if (hitPoint.y > obj.bbox[1].y - EPSILON)
		normal.y = -1.f;
	else if (hitPoint.y < obj.bbox[0].y + EPSILON)
		normal.y = -1.f;
	else if (hitPoint.x > obj.bbox[1].x - EPSILON)
		normal.x = -1.f;
	else if (hitPoint.x < obj.bbox[0].x + EPSILON)
		normal.x = -1.f;
	else if (hitPoint.z > obj.bbox[1].z - EPSILON)
		normal.z = -1.f;
	return (normal);
}

static float3			hyperboloidNormal(const float3 hitPoint)
{
	return (normalize((float3)(hitPoint.x, -hitPoint.y, hitPoint.z)));
}
*/
static float3			primitiveNormal(float3 hitPos, t_objType type)
{
	float3				normalOs;

	if (type == SPHERE)
		normalOs = sphereNormal(hitPos);
	else if (type == PLAN)
		normalOs = planNormal();
	else if (type == CYLINDRE)
		normalOs = cylindreNormal(hitPos);
/*	else if (obj.type == CONE)
		return (coneNormal(hitPoint, obj.angle));
	else if (obj.type == BOX)
		return (boxNormal(obj, hitPoint));
	else if (obj.type == DISK)
		return (diskNormal());
	else if (obj.type == HYPERBOLOID)
		return (hyperboloidNormal(hitPoint));*/
	else
		normalOs = planNormal();
	return (normalOs);
}
