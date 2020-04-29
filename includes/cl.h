#ifndef CL_H
# define CL_H

# include <OpenCL/cl.h>

# define CL_PLATFORM_UNINITIALIZED -1
# define CL_PLATFORM_MAX_AMOUNT 2

# define CL_KERNEL_AMOUNT 3

# define CL_PROGRAM_SOURCE "kernel.cl"
# define CL_PROGRAM_OPTIONS "-Wall -Wextra -Werror"

# define CL_KERNEL_0 "init"

typedef struct			s_gpu
{
	cl_device_id		id;
	cl_ulong		global_mem_size;
	cl_uint			comp_unit_nb;
	size_t			max_kernel_args_size;
	size_t			max_witems_per_wgroup;
	cl_uint			max_nd_range;
	size_t			max_witems_per_dim[3];
}				t_gpu;

typedef struct			s_gpu_buffers
{
	cl_mem			data;
	cl_mem			canvas_pixels;
	cl_mem			img_texture;
	cl_mem			ray_lum_tensor;
	cl_mem			tensor_dims;
}				t_gpu_buffers;

typedef struct			s_cl
{
	cl_platform_id		platforms[CL_PLATFORM_MAX_AMOUNT];
	cl_uint			platform_amount;
	cl_uint			gpu_platform_index;
	t_gpu			gpu;
	cl_context		context;
	cl_program		program;
	cl_command_queue	cmd_queue;
	cl_kernel		kernels[CL_KERNEL_AMOUNT];
	t_gpu_buffers		gpu_buf;
}				t_cl;

int				initOpenCL(int state);
#endif
