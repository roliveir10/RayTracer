#include <math.h>
#include "rt.h"

double					plan(t_object obj, t_vector o, t_vector dir)
{
		double			dist;

		(void)obj;
		changeReference(&o, &dir, obj);
		dist = -o.y / dir.y;
		return (dist <= 0 ? -1 : dist);
}

double					sphere(t_object obj, t_vector o, t_vector dir)
{
	double				a;
	double				b;
	double				c;

	changeReference(&o, &dir, obj);
	a = ft_dot(dir, dir);
	b = 2 * ft_dot(dir, o);
	c = ft_dot(o, o) - pow(obj.radius, 2);
	return (ft_2nd_degree(a, b, c));

}

double					cylindre(t_object obj, t_vector o, t_vector dir)
{
	double				a;
	double				b;
	double				c;

	changeReference(&o, &dir, obj);
	a = pow(dir.x, 2) + pow(dir.z, 2);
	b = 2 * (dir.x * o.x + dir.z * o.z);
	c = pow(o.x, 2) + pow(o.z, 2) - pow(obj.radius, 2);
	return (ft_2nd_degree(a, b, c));
}

double					cone(t_object obj, t_vector o, t_vector dir)
{
	double				a;
	double				b;
	double				c;

	changeReference(&o, &dir, obj);
	a = pow(dir.x, 2) + pow(dir.z, 2) - pow(dir.y * tan(obj.angle), 2);
	b = 2 * (dir.x * o.x + dir.z * o.z - dir.y * tan(obj.angle) * o.y * tan(obj.angle));
	c = pow(o.x, 2) + pow(o.z, 2) - pow(o.y * tan(obj.angle), 2);
	return (ft_2nd_degree(a, b, c));
}
