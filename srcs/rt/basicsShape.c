#include <math.h>
#include "rt.h"

double					plan(t_object obj, t_vector o, t_vector dir)
{
		(void)obj;
		(void)o;
		(void)dir;
		return (0);
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
		(void)obj;
		(void)o;
		(void)dir;
		return (0);
}

double					cone(t_object obj, t_vector o, t_vector dir)
{
		(void)obj;
		(void)o;
		(void)dir;
		return (0);
}
