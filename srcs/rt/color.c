#include "rt.h"

t_vector		setColor(int color)
{
	t_vector	vcolor;

	vcolor.x = (double)(color >> 16 & 0xFF) / 255;
	vcolor.y = (double)(color >> 8 & 0xFF) / 255;
	vcolor.z = (double)(color & 0xFF) / 255;
	return (vcolor);
}
