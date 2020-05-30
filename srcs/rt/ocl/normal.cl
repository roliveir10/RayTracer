static float3				sphereNormal(const float3 hitPoint)
{
	return (hitPoint);
}

static float3				planNormal(void)
{
	return ((float3)(0.f, 1.f, 0.f));
}

static float3				infCylindreNormal(float3 hitPoint)
{
	return ((float3)(hitPoint.x, 0.f, hitPoint.z));
}

static float3				cylindreNormal(float3 hitPoint)
{
	if (fabs((float)(hitPoint.y - 1.f)) < EPSILON)
		return ((float3)(0.f, 1.f, 0.f));
	else if (fabs((float)(hitPoint.y + 1.f)) < EPSILON)
		return ((float3)(0.f, -1.f, 0.f));
	return ((float3)(hitPoint.x, 0.f, hitPoint.z));
}

static float3				infConeNormal(float3 hitPoint)
{
	float3					normal;

	normal = (float3)(hitPoint.x, -hitPoint.y, hitPoint.z);
	return (normalize(normal));
}

static float3				coneNormal(float3 hitPoint)
{
	float3					normal;

	if (fabs(hitPoint.y + 1.f) < EPSILON)
		normal = (float3)(0.f, -1.f, 0.f);
	else
	{
		normal = (float3)(hitPoint.x, -hitPoint.y, hitPoint.z);
		normal = normalize(normal);
	}
	return (normal);
}

static float3				cubeNormal(float3 hitPoint)
{
	return (sign(hitPoint) * normalize(fmax(fabs(hitPoint) - 1.f + EPSILON, 0.f)));
	/*if (fabs((float)(hitPoint.x - 1.f)) <= EPSILON)
		return ((float3)(1.f, 0.f, 0.f));
	else if (fabs((float)(hitPoint.x + 1.f)) <= EPSILON)
		return ((float3)(-1.f, 0.f, 0.f));
	else if (fabs((float)(hitPoint.y - 1.f)) <= EPSILON)
		return ((float3)(0.f, 1.f, 0.f));
	else if (fabs((float)(hitPoint.y + 1.f)) <= EPSILON)
		return ((float3)(0.f, -1.f, 0.f));
	else if (fabs((float)(hitPoint.z - 1.f)) <= EPSILON)
		return ((float3)(0.f, 0.f, 1.f));
	else if (fabs((float)(hitPoint.z + 1.f)) <= EPSILON)
		return ((float3)(0.f, 0.f, -1.f));
	return ((float3)(0.f, 0.f, 0.f));
*/
}

static float3			infHyperboloidNormal(const float3 hitPoint)
{
	return (normalize((float3)(hitPoint.x, -hitPoint.y, hitPoint.z)));
}

/*static float3			roundedboxNormal(float3 hitPoint)
{
	return (sign(hitPoint) * normalize(fmax(fabs(hitPoint) - 1.f, 0.f)));
}*/

static float3			primitiveNormal(float3 hitPos, t_objType type)
{
	float3				normalOs;

	if (type == SPHERE)
		normalOs = sphereNormal(hitPos);
	else if (type == PLAN || type == DISK || type == RECTANGLE || type == TRIANGLE)
		normalOs = planNormal();
	else if (type == INFCYLINDRE)
		normalOs = infCylindreNormal(hitPos);
	else if (type == CYLINDRE)
		normalOs = cylindreNormal(hitPos);
	else if (type == INFCONE)
		normalOs = infConeNormal(hitPos);
	else if (type == CONE)
		normalOs = coneNormal(hitPos);
	else if (type == CUBE)
		normalOs = cubeNormal(hitPos);
	else if (type == INFHYPERBOLOID)
		normalOs = infHyperboloidNormal(hitPos);
//	else if (type == ROUNDEDBOX)
//		normalOs = roundedboxNormal(hitPos);
	else
		normalOs = planNormal();
	return (normalOs);
}
