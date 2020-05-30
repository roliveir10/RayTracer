static float		ft_clamp(float value, float lo, float hi)
{
	if (value < lo)
		return (lo);
	else if (value > hi)
		return (hi);
	return (value);
}

static bool			hitPosInBbox(float3 pos, t_bbox aabb)
{
	return (aabb.vmin.x - EPSILON < pos.x && pos.x < aabb.vmax.x + EPSILON
				&& aabb.vmin.y - EPSILON < pos.y && pos.y < aabb.vmax.y + EPSILON
				&& aabb.vmin.z - EPSILON < pos.z && pos.z < aabb.vmax.z + EPSILON);
}

static bool		ft_2nd_degree(float2 *roots, float3 quad)
{
	float		delta;
	float		den;

	delta = quad.y * quad.y - 4.f * quad.x * quad.z;
	if (delta < 0.f)
	{
		roots->x = roots->y = 0.f / 0.f;
		return (false);
	}
	den = 0.5f / quad.x;
	delta = sqrt(delta);
	roots->x = (-quad.y + delta) * den;
	roots->y = (-quad.y - delta) * den;
	return (true);
}

static float16		mat44Transpose(float16 mat44)
{
	return (mat44.s048C159D26AE37BF);
}

static float3		applyLinearMatrice(float16 mat44, float3 vec3)
{
	float3			res;

	res.x = dot(mat44.s048, vec3);
	res.y = dot(mat44.s159, vec3);
	res.z = dot(mat44.s26A, vec3);
	return (res);
}

static float3		applyHomogeneousMatrice(float16 mat44, float3 vec3)
{
	float4			tmp;
	float3			res;

	tmp.xyz = vec3;
	tmp.w = 1.f;
	res.x = dot(mat44.s048C, tmp);
	res.y = dot(mat44.s159D, tmp);
	res.z = dot(mat44.s26AE, tmp);
	return (res);
}

static uint			getRand(uint2 * rand_s)
{
	rand_s->x = 36969 * (rand_s->x & 0xFFFF) + (rand_s->x >> 16);
	rand_s->y = 18000 * (rand_s->y & 0xFFFF) + (rand_s->y >> 16);
	uint			n = (rand_s->x << 16) + (rand_s->y);

	return (n);
}

static float		frand0To1(uint2 * random_seeds)
{
	int				n;

	n = getRand(random_seeds);
	union
	{
		float f;
		uint ui;
	}
	fui;

	fui.ui = (n & 0x007fffff) | 0x3F800000;
	return (fui.f - 1.f);
}

static float3		f3randMinusHalf(uint2 *random_seeds)
{
	return ((float3)(frand0To1(random_seeds) - 0.5f,
					frand0To1(random_seeds) - 0.5f,
					frand0To1(random_seeds) - 0.5f));
}

static float3		randDirCoshemi
(
					uint2	*random_seeds,
					float3	axis
)
{
	float3			randdir;
	float2			seed;
	float			tmp;
	float3			vtan1;
	float3			vtan2;
	float16			lin_mat;

	seed.x = TAU * frand0To1(random_seeds);
	seed.y = frand0To1(random_seeds);
	tmp = sqrt((float)(1.f - seed.y));
	randdir = (float3)(cos(seed.x) * tmp, sin(seed.x) * tmp, sqrt(seed.y));
	vtan1 = f3randMinusHalf(random_seeds);
	vtan1 = cross(axis, vtan1);
	vtan1 = normalize(vtan1);
	vtan2 = cross(vtan1, axis);
	lin_mat.s012 = vtan1;
	lin_mat.s456 = vtan2;
	lin_mat.s89A = axis;
	randdir = applyLinearMatrice(lin_mat, randdir);
	return (randdir);
}

static float3		randDirCosLob
(
	uint2			*random_seeds,
	float3			axis,
	float			shininess
)
{
	float3			randdir;
	float2			seed;
	return (axis);
}

static float16		buildDiagonalMat33in44(float3 diag)
{
	float16			result = (float16)(0.f);

	result.s05AF = (float4)(diag.x, diag.y, diag.z, 1.f);
	return (result);
}

static float16		buildRotationMat33in44(float theta, int axis)
{
	float16			result;
	float			cosTh;
	float			sinTh;

	result = buildDiagonalMat33in44((float3)(1.f, 1.f, 1.f));
	axis = axis % 3;
	sinTh = sincos(theta, &cosTh);
	if (axis == 0)
		result.s5A69 = (float4)(cosTh, cosTh, sinTh, -sinTh);
	else if (axis == 1)
		result.sA082 = (float4)(cosTh, cosTh, sinTh, -sinTh);
	else
		result.s0514 = (float4)(cosTh, cosTh, sinTh, -sinTh);
	return (result);
}

static float16		mat44Mul(float16 const mat_A, float16 const mat_B)
{
	float16			mat_C;

	mat_C.s0 = dot(mat_A.s048C, mat_B.s0123);
	mat_C.s1 = dot(mat_A.s159D, mat_B.s0123);
	mat_C.s2 = dot(mat_A.s26AE, mat_B.s0123);
	mat_C.s3 = dot(mat_A.s37BF, mat_B.s0123);
	mat_C.s4 = dot(mat_A.s048C, mat_B.s4567);
	mat_C.s5 = dot(mat_A.s159D, mat_B.s4567);
	mat_C.s6 = dot(mat_A.s26AE, mat_B.s4567);
	mat_C.s7 = dot(mat_A.s37BF, mat_B.s4567);
	mat_C.s8 = dot(mat_A.s048C, mat_B.s89AB);
	mat_C.s9 = dot(mat_A.s159D, mat_B.s89AB);
	mat_C.sA = dot(mat_A.s26AE, mat_B.s89AB);
	mat_C.sB = dot(mat_A.s37BF, mat_B.s89AB);
	mat_C.sC = dot(mat_A.s048C, mat_B.sCDEF);
	mat_C.sD = dot(mat_A.s159D, mat_B.sCDEF);
	mat_C.sE = dot(mat_A.s26AE, mat_B.sCDEF);
	mat_C.sF = dot(mat_A.s37BF, mat_B.sCDEF);
	return (mat_C);
}

static float			mat33in44Det(float16 const mat33in44)
{
	return (mat33in44.s0 * mat33in44.s5 * mat33in44.sA
			+ mat33in44.s1 * mat33in44.s6 * mat33in44.s8
			+ mat33in44.s2 * mat33in44.s4 * mat33in44.s9
			- mat33in44.s2 * mat33in44.s5 * mat33in44.s8
			- mat33in44.s1 * mat33in44.s4 * mat33in44.sA
			- mat33in44.s0 * mat33in44.s6 * mat33in44.s9);
}

static float16			mat33in44Inv(float16 const mat33)
{
	float		det;
	float16		result;

	if (fabs((det = mat33in44Det(mat33))) < EPSILON)
		return ((float16)(0.f / 0.f));
	result.s0 = mat33.s5 * mat33.sA - mat33.s6 * mat33.s9;
	result.s4 = mat33.s6 * mat33.s8 - mat33.s4 * mat33.sA;
	result.s8 = mat33.s4 * mat33.s9 - mat33.s5 * mat33.s8;
	result.s1 = mat33.s2 * mat33.s9 - mat33.s1 * mat33.sA;
	result.s5 = mat33.s0 * mat33.sA - mat33.s2 * mat33.s8;
	result.s9 = mat33.s1 * mat33.s8 - mat33.s0 * mat33.s9;
	result.s2 = mat33.s1 * mat33.s6 - mat33.s2 * mat33.s5;
	result.s6 = mat33.s2 * mat33.s4 - mat33.s0 * mat33.s6;
	result.sA = mat33.s0 * mat33.s5 - mat33.s1 * mat33.s4;
	result = (float16)(native_recip((float)det)) * (result);
	result.s37B = (float3)(0.f, 0.f, 0.f);
	result.sCDEF = (float4)(0.f, 0.f, 0.f, 1.f);
	return (result);
}
