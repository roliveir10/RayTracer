#include "rt.h"

/*
**	cl_int clGetDeviceInfo(
**		cl_device_id device, 			//gpu id
**		cl_device_info param_name,		// a flag, see man
**		size_t param_value_size,		// sizeof(*(pointer passed param_value))
**		void *param_value,				// returns queried arg value
**		size_t *param_value_size_ret)	// returns actual size of return arg
**	return CL_SUCCESS, CL_INVALID_DEVICE or
*/

/*
** 1 thread (work item) per core; each compute unit on the gpu may have
**	multiple cores
**
** work group size = product of work group dim(i) ; also equal to number of
**	threads (work items) in work group. This number should always be a multiple
**	of the number of cores per compute unit (cpcu generally = 16 on nvidia
**	and 64 on AMD).
**
** CL_QUEUE_SIZE
**
** CL_DEVICE_VENDOR						:
** CL_DEVICE_NAME						:
** CL_DRIVER_VERSION					:
** CL_DEVICE_PROFILE					:
** CL_DEVICE_VERSION					:
** CL_DEVICE_OPENCL_C_VERSION			:
** CL_DEVICE_MAX_COMPUTE_UNITS			:
** CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS	:
** CL_DEVICE_MAX_WORK_ITEM_SIZES		:
** CL_DEVICE_MAX_WORK_GROUP_SIZE		:
** CL_DEVICE_MEM_BASE_ADDR_ALIGN 		:
** CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE	:
** CL_DEVICE_MAX_CLOCK_FREQUENCY		:
** CL_DEVICE_LOCAL_MEM_SIZE				:
** CL_DEVICE_MAX_MEM_ALLOC_SIZE			:
**
** cl_int clGetPlatformInfo( 	cl_platform_id platform,
**   	cl_platform_info param_name, //CL_PLATFORM_...
**   	size_t param_value_size,
**   	void *param_value,
**   	size_t *param_value_size_ret)
** CL_PLATFORM_PROFILE
** CL_PLATFORM_VERSION
** CL_PLATFORM_NAME
** CL_PLATFORM_VENDOR
*/

static void		printDeviceInfo(char *gpu_name, char *platform_name, char *gpu_ocl_version)
{
	printf("Platform index : %d\n", g_env.ocl.gpu_platform_index);
	printf("Platform name: %s\n", platform_name);
	printf("Device name: %s\n", gpu_name);
	printf("Version %s\n", gpu_ocl_version);
	printf("- global mem size: %llu\n", g_env.ocl.gpu.global_mem_size);
	printf("- comput units: %d\n", g_env.ocl.gpu.comp_unit_nb);
	printf("- max kernel args size: %zu\n", g_env.ocl.gpu.max_kernel_args_size);
	printf("- Max work items per group: %zu\n", g_env.ocl.gpu.max_witems_per_wgroup);
	printf("- Max nD range: %d\n", g_env.ocl.gpu.max_nd_range);
	printf("- Max word items per dim:\n");
	printf("\t- x: %zu\n", g_env.ocl.gpu.max_witems_per_dim[0]);
	printf("\t- y: %zu\n", g_env.ocl.gpu.max_witems_per_dim[1]);
	printf("\t- z: %zu\n", g_env.ocl.gpu.max_witems_per_dim[2]);
}

static void		clSetDeviceInfo(void)
{
	char		gpu_name[256];
	char		platform_name[256];
	char		gpu_cl_version[16];

	clGetPlatformInfo(g_env.ocl.platforms[g_env.ocl.gpu_platform_index],
		CL_PLATFORM_NAME, 256, platform_name, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_GLOBAL_MEM_SIZE,
		sizeof(cl_ulong), &g_env.ocl.gpu.global_mem_size, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_COMPUTE_UNITS,
		sizeof(cl_ulong), &g_env.ocl.gpu.comp_unit_nb, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_NAME, 256, gpu_name, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_VERSION, 16, gpu_cl_version, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_PARAMETER_SIZE,
		sizeof(size_t), &g_env.ocl.gpu.max_kernel_args_size, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_WORK_GROUP_SIZE,
		sizeof(size_t), &g_env.ocl.gpu.max_witems_per_wgroup, NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
		sizeof(cl_uint), &(g_env.ocl.gpu.max_nd_range), NULL);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
		sizeof(size_t) * g_env.ocl.gpu.max_nd_range,
		&g_env.ocl.gpu.max_witems_per_dim, NULL);
	printDeviceInfo(gpu_name, platform_name, gpu_cl_version);
}

static int		clInitializePlatforms(void)
{
	int		gpu = 0;

	if (clGetPlatformIDs(CL_PLATFORM_MAX_AMOUNT, g_env.ocl.platforms,
		&(g_env.ocl.platform_amount)) < 0)
		return (0);
	g_env.ocl.gpu_platform_index = -1;
	while (!gpu && ++g_env.ocl.gpu_platform_index < g_env.ocl.platform_amount)
	{
		if (clGetDeviceIDs(g_env.ocl.platforms[g_env.ocl.gpu_platform_index],
			CL_DEVICE_TYPE_GPU, 1, &g_env.ocl.gpu.id, NULL) == CL_SUCCESS)
			gpu = 1;
	}
	return (gpu);
}

static int		clPlatformData(int platform_index)
{
	if (platform_index == CL_PLATFORM_UNINITIALIZED)
	{
		if (!clInitializePlatforms())
			return (0);
	}
	else
	{
		g_env.ocl.gpu_platform_index = platform_index;
		if (clGetDeviceIDs(g_env.ocl.platforms[g_env.ocl.gpu_platform_index],
			CL_DEVICE_TYPE_GPU, 1, &g_env.ocl.gpu.id, NULL) < 0)
			return (0);
	}
	printf("Platform amount found: %d\n", g_env.ocl.platform_amount);
	clSetDeviceInfo();
	return (1);
}

int			initOpenCL(int platform_index)
{
	if (!clPlatformData(platform_index))
	{
		printf("Could not find an appropriate GPU/platform. Aborting...\n");
		return (0);
	}
	return (1);
}
