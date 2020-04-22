#include <math.h>
#include "rt.h"

double				plan(__unused t_object obj, t_vector o, t_vector dir)
{
	t_solution		sol;

	ft_bzero(&sol, sizeof(sol));
	changeReference(&o, &dir, obj);
	if (dir.y)
	{
		sol.nbrSol = 1;
		sol.sol[0] = -o.y / dir.y;
	}
	return (limit(o, dir, sol, obj));
}

double					sphere(t_object obj, t_vector o, t_vector dir)
{
	double				a;
	double				b;
	double				c;
	t_solution			sol;

	changeReference(&o, &dir, obj);
	a = ft_dot(dir, dir);
	b = 2 * ft_dot(dir, o);
	c = ft_dot(o, o) - pow(obj.radius, 2);
	sol = ft_2nd_degree(a, b, c);
	return (limit(o, dir, sol, obj));

}

double					cylindre(t_object obj, t_vector o, t_vector dir)
{
	double				a;
	double				b;
	double				c;
	t_solution			sol;

	changeReference(&o, &dir, obj);
	a = pow(dir.x, 2) + pow(dir.z, 2);
	b = 2 * (dir.x * o.x + dir.z * o.z);
	c = pow(o.x, 2) + pow(o.z, 2) - pow(obj.radius, 2);
	sol = ft_2nd_degree(a, b, c);
	return (limit(o, dir, sol, obj));
}

double					cone(t_object obj, t_vector o, t_vector dir)
{
	double				a;
	double				b;
	double				c;
	t_solution			sol;

	changeReference(&o, &dir, obj);
	a = pow(dir.x, 2) + pow(dir.z, 2) - pow(dir.y * tan(obj.angle), 2);
	b = 2 * (dir.x * o.x + dir.z * o.z - dir.y * tan(obj.angle) * o.y * tan(obj.angle));
	c = pow(o.x, 2) + pow(o.z, 2) - pow(o.y * tan(obj.angle), 2);
	sol = ft_2nd_degree(a, b, c);
	return (limit(o, dir, sol, obj));
}
