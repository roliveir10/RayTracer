static float4		quaternionMul(float4 quat_a, float4 quat_b)
{
	float4			new;

	new.x = quat_a.w * quat_b.x + quat_a.x * quat_b.w
		+ quat_a.y * quat_b.z - quat_a.z * quat_b.y;
	new.y = quat_a.w * quat_b.y - quat_a.x * quat_b.z
		+ quat_a.y * quat_b.w + quat_a.z * quat_b.x;
	new.z = quat_a.w * quat_b.z + quat_a.x * quat_b.y
		- quat_a.y * quat_b.x + quat_a.z * quat_b.w;
	new.w = quat_a.w * quat_b.w - quat_a.x * quat_b.x
		- quat_a.y * quat_b.y - quat_a.z * quat_b.z;
	return (new);
}

static float4		quaternionConj(float4 quat)
{
	return ((float4){-quat.x, -quat.y, -quat.z, quat.w});
}

static float3		quatRotWithQuat(float3 vec, float4 quatRotVec)
{
	float4		quatVecDir;
	float4		quatResult;

	quatVecDir.x = vec.x;
	quatVecDir.y = vec.y;
	quatVecDir.z = vec.z;
	quatVecDir.w = 0;
	quatResult = quaternionMul(quatRotVec, quatVecDir);
	quatResult = quaternionMul(quatResult, quaternionConj(quatRotVec));
	vec.x = quatResult.x;
	vec.y = quatResult.y;
	vec.z = quatResult.z;
	return (vec);
}
