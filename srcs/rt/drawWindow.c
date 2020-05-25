#include "rt.h"

/*static void				addPixel(t_vector color, int x, int y)
{
	unsigned char		rgb[3];
	unsigned int		color_rgb;
	int					pos;

	rgb[0] = (unsigned char)(ft_clamp(pow(color.x, .454545), 0, 1) * 255);
	rgb[1] = (unsigned char)(ft_clamp(pow(color.y, .454545), 0, 1) * 255);
	rgb[2] = (unsigned char)(ft_clamp(pow(color.z, .454545), 0, 1) * 255);
	color_rgb = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	for (int i = 0; i < g_env.scene.pixPerUnit; i++)
		for (int j = 0; j < g_env.scene.pixPerUnit; j++)
		{
			if ((pos = (y + i) * g_env.scene.screenX + (x + j)) < g_env.resolution)
				g_env.lib.image[pos] = color_rgb;
		}
}
*/

int						drawWindow(void)
{
	int					error;

	if ((error = executeKernel0()) < 0)
	{
		dprintf(2, "Error code: %d\n", error);
		return (0);
	}
	return (1);
}
