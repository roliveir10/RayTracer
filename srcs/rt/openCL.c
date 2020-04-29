#include "rt.h"

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

static int		clCreateContextAndQueue(void)
{
	cl_int		error;

	g_env.ocl.context = clCreateContext(NULL, 1, &g_env.ocl.gpu.id, NULL, NULL, &error);
	if (error < 0)
		return (0);
	g_env.ocl.cmd_queue = clCreateCommandQueue(g_env.ocl.context,
			g_env.ocl.gpu.id, 0, &error);
	return (error >= 0);
}

static int		clReadAndBuildProgram(void)
{
	int		fd;
	cl_int		error;
	char		*file_buf;
	size_t		file_len;

	if ((fd = open(CL_PROGRAM_SOURCE, O_RDONLY)) == -1)
		return (0);
	if (!ft_readfile(fd, &file_buf, (size_t)-1))
		return (0);
	file_len = ft_strlen(file_buf);
	g_env.ocl.program = clCreateProgramWithSource(g_env.ocl.context, 1,
		(char const **)&filebuf, &file_len, &error);
	free(file_buf);
	if (error < 0)
		return (0);
	if (!(error = clBuildProgram(g_env.ocl.program, 1, &g_env.ocl.gpu.id,
			CL_PROGRAM_OPTIONS, NULL, NULL)) < 0)
		return (0);
	close(fd);
	return (1);
}

static int		clInitGpuMemory(void)
{
	int		error;

	g_env.ocl.gpu_buf.data = clCreateBuffer(g_env.ocl.context,
		CM_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		sizeof(t_data), &g_env.data, &error);
	if (error < 0)
		return (0);
	g_env.ocl.gpu_buf.img_texture = clCreateBuffer(g_env.ocl.context,
		CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(uint32_t) * 100 * 100, g_env.img_texture, &error);
	if (error < 0)
		return (0);
	f_env.ocl.gpu_buf.canvas_pixels = clCreateBuffer(g_env.ocl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(uint32_t) * g_env.resolution, g_env.lib->image, &error);
	return (error >= 0);
}

static int		clInitKernel(void)
{
	int		error = 1;

	g_rt.ocl.kernels[1] = clCreateKernel(g_env.ocl.program, CL_KERNEL_0, &error);
	if (error < 0)
		return (0);
	return (1);
}

int			initOpenCL(int platform_index)
{
	if (!clPlatformData(platform_index))
	{
		dprintf(2, "Could not find an appropriate GPU/platform. Aborting...\n");
		return (0);
	}
	if (!clCreateContextAndQueue())
	{
		dprintf(2, "Could not create device, context or queue. Aborting...\n");
		return (0);
	}
	if (!clReadAndBuildProgram())
	{
		dprintf(2, "Could not build program. Aborting...\n");
		return (0);
	}
	if (!clInitGpuMemory())
	{
		dprintf(2, "Could not initialize gpu memory buffers. Aborting...\n");
		return (0);"
	}
	if (!clInitKernel())
	{
		dprintf(2, "Could not initialize kernels. Aborting...\n");
		return (0);
	}
	return (1);
}
