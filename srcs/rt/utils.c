#include <math.h>
#include "rt.h"

cl_float3			vec3mul(cl_float3 f, float mul)
{
	return ((cl_float3){{f.x * mul, f.y * mul, f.z * mul}});
}

float				vec3d_length2(cl_float3 vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

cl_float3			vec3d_unit(cl_float3 vec)
{
	float			length;

	length = sqrt(vec3d_length2(vec));
	return ((cl_float3){{vec.x / length, vec.y / length, vec.z / length}});
}

cl_float3			clFl3(float x, float y, float z)
{
	cl_float3		vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

