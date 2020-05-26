#define CL_SILENCE_DEPRECATION
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "rt.h"

void			delOpenCL(t_cl *ocl)
{
	if (clFinish(ocl->cmd_queue))
		return ;
	if (clReleaseKernel(ocl->kernels[0]))
		return ;
	if (clReleaseKernel(ocl->kernels[1]))
		return ;
	if (clReleaseKernel(ocl->kernels[2]))
		return ;
	if (clReleaseMemObject(ocl->gpu_buf.canvas_pixels))
		return ;
	ocl->gpu_buf.canvas_pixels = NULL;
	if (clReleaseMemObject(ocl->gpu_buf.scene))
		return ;
	ocl->gpu_buf.scene = NULL;
	if (clReleaseCommandQueue(ocl->cmd_queue))
		return ;
	if (clReleaseContext(ocl->context))
		return ;
	if (clReleaseProgram(ocl->program))
		return ;
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
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_COMPUTE_UNITS,
				sizeof(cl_ulong), &g_env.ocl.gpu.comp_unit_nb, NULL);
	printf("- compute units: %u\n", g_env.ocl.gpu.comp_unit_nb);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_WORK_GROUP_SIZE,
				sizeof(size_t), &g_env.ocl.gpu.max_witems_per_wgroup, NULL);
	printf("- max work items per group %zu\n", g_env.ocl.gpu.max_witems_per_wgroup);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
				sizeof(cl_uint), &g_env.ocl.gpu.max_nd_range, NULL);
	printf("- max nD range: %u\n", g_env.ocl.gpu.max_nd_range);
	clGetDeviceInfo(g_env.ocl.gpu.id, CL_DEVICE_MAX_WORK_ITEM_SIZES,
				sizeof(size_t) * g_env.ocl.gpu.max_nd_range,
				&g_env.ocl.gpu.max_witems_per_dim, NULL);
	printf("- max work items per dim:\n");
	printf("\t- x: %zu\n", g_env.ocl.gpu.max_witems_per_dim[0]);
	printf("\t- y: %zu\n", g_env.ocl.gpu.max_witems_per_dim[1]);
	printf("\t- z: %zu\n", g_env.ocl.gpu.max_witems_per_dim[2]);
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
	size_t len = 0;
	cl_int ret = CL_SUCCESS;

	if ((fd = open(RT_CL_PROGRAM_SOURCE, O_RDONLY)) == -1)
		return (0);
	if (!ft_readFile(fd, &file_buf, (size_t)-1))
		return (0);
	file_len = ft_strlen(file_buf);
	g_env.ocl.program = clCreateProgramWithSource(g_env.ocl.context, 1,
		(char const **)&file_buf, &file_len, &error);
	ft_strdel(&file_buf);
	if (error < 0)
		return (0);
	if ((error = clBuildProgram(g_env.ocl.program, 1, &g_env.ocl.gpu.id,
			NULL, NULL, NULL)) < 0)
	{
		ret = clGetProgramBuildInfo(g_env.ocl.program, g_env.ocl.gpu.id, CL_PROGRAM_BUILD_LOG, 0, NULL, &len);
		char *buffer = calloc(len, sizeof(char));
		ret = clGetProgramBuildInfo(g_env.ocl.program, g_env.ocl.gpu.id, CL_PROGRAM_BUILD_LOG, len, buffer, NULL);
		printf("log: %s\n error code: %d", buffer, error);
		ft_strdel(&buffer);
			return (0);
	}
	close(fd);
	return (1);
}

static int		clInitGpuMemory(void)
{
	int		error;

	g_env.ocl.gpu_buf.canvas_pixels = clCreateBuffer(g_env.ocl.context,
		CL_MEM_WRITE_ONLY, sizeof(cl_uint) * g_env.resolution,
		NULL, &error);
	g_env.ocl.gpu_buf.scene = clCreateBuffer(g_env.ocl.context,
		CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_scene),
		&g_env.scene, &error);
	return (error >= 0);
}

static int		clInitKernel(void)
{
	int		error = 1;

	g_env.ocl.kernels[0] = clCreateKernel(g_env.ocl.program, CL_KERNEL_0, &error);
	if (error < 0)
		return (0);
	g_env.ocl.kernels[1] = clCreateKernel(g_env.ocl.program, CL_KERNEL_1, &error);
	if (error < 0)
		return (0);
	g_env.ocl.kernels[2] = clCreateKernel(g_env.ocl.program, CL_KERNEL_2, &error);
	if (error < 0)
		return (0);
	return (1);
}

int				initOpenCL(int platform_index)
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
		return (0);
	}
	if (!clInitKernel())
	{
		dprintf(2, "Could not initialize kernels. Aborting...\n");
		return (0);
	}
	return (1);
}

static int			setUpKernel0(void)
{
	int				error;

	if ((error = clSetKernelArg(g_env.ocl.kernels[0], 0, sizeof(cl_mem),
			&g_env.ocl.gpu_buf.ray)) < 0)
		return (error);
	if ((error = clSetKernelArg(g_env.ocl.kernels[0], 1, sizeof(cl_mem),
			&g_env.ocl.gpu_buf.scene)) < 0)
		return (error);
	return (1);
}

static int			setUpKernel1(void)
{
	int				error;

	if ((error = clSetKernelArg(g_env.ocl.kernels[1], 0, sizeof(cl_mem),
			&g_env.ocl.gpu_buf.canvas_pixels)) < 0)
		return (error);
	if ((error = clSetKernelArg(g_env.ocl.kernels[1], 1, sizeof(cl_mem),
			&g_env.ocl.gpu_buf.ray)) < 0)
		return (error);
	if ((error = clSetKernelArg(g_env.ocl.kernels[1], 2, sizeof(cl_mem),
			&g_env.ocl.gpu_buf.global_dims)) < 0)
		return (error);
	return (1);
}

static int			setUpKernel2(void)
{
	int				error;
	const size_t	nbrObject = (size_t)g_env.scene.nbrObject;

	if ((error = clEnqueueWriteBuffer(g_env.ocl.cmd_queue, g_env.ocl.gpu_buf.scene,
			CL_TRUE, 0, sizeof(t_scene), &(g_env.scene), 0, NULL, NULL)) < 0)
		return (error);
	if ((error = clSetKernelArg(g_env.ocl.kernels[2], 0, sizeof(cl_mem),
			&g_env.ocl.gpu_buf.scene)) < 0)
		return (error);
	if ((error = clEnqueueNDRangeKernel(g_env.ocl.cmd_queue, g_env.ocl.kernels[2],
			1, NULL, &nbrObject, NULL, 0, NULL, NULL)) < 0)
		return (error);
	return (1);
}

static int			initWorkStepAndRayBuffer(void)
{
	cl_int3			*wksteps = &g_env.scene.work_steps;
	int				error;

	wksteps->x = ft_min(ft_min(64, g_env.ocl.gpu.max_witems_per_dim[0]),
			g_env.scene.work_dims.x);
	wksteps->y = ft_min(ft_min(64, g_env.ocl.gpu.max_witems_per_dim[1]),
			g_env.scene.work_dims.y);
	wksteps->z = ft_min(ft_min(128, g_env.ocl.gpu.max_witems_per_dim[2]),
			g_env.scene.work_dims.z);
	g_env.ocl.gpu_buf.ray = clCreateBuffer(g_env.ocl.context, CL_MEM_READ_WRITE,
			sizeof(cl_float3) * wksteps->x * wksteps->y * g_env.scene.work_dims.z,
			NULL, &error);
	if (error < 0)
		return (error);
	return (1);
}

static int			initGlobalDims(void)
{
	cl_uint8		global_dims;
	int				error;

	global_dims = (cl_uint8){{g_env.scene.work_steps.x, g_env.scene.work_steps.y,
			g_env.scene.work_steps.z, 0, g_env.scene.work_dims.x,
			g_env.scene.work_dims.y, g_env.scene.work_dims.z, 0}};
	g_env.ocl.gpu_buf.global_dims = clCreateBuffer(g_env.ocl.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint8),
			&global_dims, &error);
	if (error < 0)
		return (error);
	if ((error = clEnqueueWriteBuffer(g_env.ocl.cmd_queue,
			g_env.ocl.gpu_buf.global_dims, CL_TRUE, 0, sizeof(cl_uint8),
			&global_dims, 0, NULL, NULL)) < 0)
		return (error);
	return (1);
}

static int			renderEnqueuePairwiseKernels(void)
{
	t_sizet3		work_offsets;
	t_sizet3		work_dim_end;
	int				error;

	work_offsets.y = 0;
	while (work_offsets.y < (size_t)g_env.scene.work_dims.y)
	{
		work_offsets.x = 0;
		while (work_offsets.x < (size_t)g_env.scene.work_dims.x)
		{
			work_offsets.z = 0;
			while (work_offsets.z < (size_t)g_env.scene.work_dims.z)
			{
				work_dim_end.x = (size_t)g_env.scene.work_steps.x;
				work_dim_end.y = (size_t)g_env.scene.work_steps.y;
				work_dim_end.z  = (size_t)g_env.scene.work_steps.z;
				if ((error = clEnqueueNDRangeKernel(g_env.ocl.cmd_queue,
						g_env.ocl.kernels[0], 3, (size_t const *)&work_offsets,
						(size_t const *)&work_dim_end, NULL, 0, NULL, NULL)) < 0)
					return (error);
				work_offsets.z += g_env.scene.work_steps.z;
			}
			if ((error = clFinish(g_env.ocl.cmd_queue)) < 0)
				return (error);
			if ((error = clEnqueueNDRangeKernel(g_env.ocl.cmd_queue,
					g_env.ocl.kernels[1], 2, (size_t const *)&work_offsets,
					(size_t const *)&work_dim_end, NULL, 0, NULL, NULL)) < 0)
				return (error);
			work_offsets.x += g_env.scene.work_steps.x;
		}
		work_offsets.y += g_env.scene.work_steps.y;
		drawBar(&g_env.lib, (float)work_offsets.y / g_env.scene.work_dims.y * g_env.lib.load.loadRect.w, 1);
		printf("Progress: %f\n", (float)work_offsets.y * 100.f / g_env.scene.work_dims.y);
	}
	return (1);
}

int					executeKernel0(void)
{
	int				error;

	if ((error = setUpKernel2()) < 0)
	{
		dprintf(2, "Failed to setup kernel2\n");
		return (error);
	}
	if ((error = clFinish(g_env.ocl.cmd_queue)) < 0)
		return (error);
	if ((error = initWorkStepAndRayBuffer()) < 0)
	{
		dprintf(2, "Failed to init work step and ray buffer\n");
		return (error);
	}
	if ((error = initGlobalDims()) < 0)
	{
		dprintf(2, "Failed to init global dim\n");
		return (error);
	}
	if ((error = setUpKernel0()) < 0)
	{
		dprintf(2, "Failed to setup kernel0\n");
		return (error);
	}
	if ((error = setUpKernel1()) < 0)
	{
		dprintf(2, "Failed to setup kernel1\n");
		return (error);
	}
	if ((error = renderEnqueuePairwiseKernels()) < 0)
	{
		dprintf(2, "Failed to enqueue pairwise kernels\n");
		return (error);
	}
	if ((error = clFinish(g_env.ocl.cmd_queue)) < 0)
		return (error);
	if ((error = clEnqueueReadBuffer(g_env.ocl.cmd_queue,
			g_env.ocl.gpu_buf.canvas_pixels, CL_TRUE, 0,
			g_env.resolution * sizeof(cl_uint), g_env.lib.image,
			0, NULL, NULL)) < 0)
		return (error);
	if (g_env.ocl.gpu_buf.ray)
		clReleaseMemObject(g_env.ocl.gpu_buf.ray);
	if (g_env.ocl.gpu_buf.global_dims)
		clReleaseMemObject(g_env.ocl.gpu_buf.global_dims);
	return (1);
}
