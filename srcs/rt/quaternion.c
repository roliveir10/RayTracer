#include "rt.h"

cl_float4		quaternionMul(cl_float4 quat_a, cl_float4 quat_b)
{
	cl_float4	new;

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

cl_float4		quaternionConj(cl_float4 quat)
{
	return ((cl_float4){{-quat.x, -quat.y, -quat.z, quat.w}});
}

cl_float3			quatRotWithQuat(cl_float3 vec, cl_float4 quatRotVec)
{
	cl_float4		quatVecDir;
	cl_float4		quatResult;

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

cl_float4			xyzRotToQuat(cl_float3 rotation)
{
	double		cosinus[3];
	double		sinus[3];
	cl_float4	quat;

	cosinus[0] = cos(rotation.x / 2);
	cosinus[1] = cos(rotation.y / 2);
	cosinus[2] = cos(rotation.z / 2);
	sinus[0] = sin(rotation.x / 2);
	sinus[1] = sin(rotation.y / 2);
	sinus[2] = sin(rotation.z / 2);
	quat.x = sinus[0] * cosinus[1] * cosinus[2] - cosinus[0] * sinus[1] * sinus[2];
	quat.y = cosinus[0] * sinus[1] * cosinus[2] + sinus[0] * cosinus[1] * sinus[2];
	quat.z = cosinus[0] * cosinus[1] * sinus[2] - sinus[0] * sinus[1] * cosinus[2];
	quat.w = cosinus[0] * cosinus[1] * cosinus[2] + sinus[0] * sinus[1] * sinus[2];
	return (quat);
}
