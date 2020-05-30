static float3				dirInCosLobFromAxis
(
	uint2					*random_seeds,
	float3					axisDir,
	float					shininess
)
{
	float					phong;

	phong = native_recip(shininess) - 1.f;
	return (randDirCosLob(random_seeds, axisDir, phong));
}

static float3				reflectDir(float3 incDir, float3 normal)
{
	return (mad(-2.f * dot(incDir, normal), normal, incDir));
}

static float3				reflectCosLob
(
	uint2					*random_seeds,
	float3					incDir,
	float3					normal,
	float					shininess
)
{
	float3					reflect;

	reflect = reflectDir(incDir, normal);
	if (shininess > 0.f)
		reflect = dirInCosLobFromAxis(random_seeds, reflect, shininess);
	return (reflect);
}
