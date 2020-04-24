#include <math.h>
#include "rt.h"

double				lowerDist(t_solution sol)
{
	double			dist;

	dist = -1;
	if (sol.sol[0] <= 0 && sol.sol[1] <= 0)
		return (-1);
	if (sol.nbrSol == 1)
		return (sol.sol[0]);
	for (int i = 0; i < sol.nbrSol; i++)
	{
		if (sol.sol[i] > 0 && (dist == -1 || sol.sol[i] < dist))
			dist = sol.sol[i];
	}
	return (dist);
}

double				plan(__unused t_object obj, t_ray ray)
{
	t_solution		sol;

	ft_bzero(&sol, sizeof(sol));
	changeReference(&ray, obj);
	if (ray.dir.y)
	{
		sol.nbrSol = 1;
		sol.sol[0] = -ray.o.y / ray.dir.y;
		if (obj.isLimited)
			return (limit(ray, sol, obj));
	}
	return (lowerDist(sol));
}

double					sphere(t_object obj, t_ray ray)
{
	double				a;
	double				b;
	double				c;
	t_solution			sol;

	changeReference(&ray, obj);
	a = ft_dot(ray.dir, ray.dir);
	b = 2 * ft_dot(ray.dir, ray.o);
	c = ft_dot(ray.o, ray.o) - pow(obj.radius, 2);
	sol = ft_2nd_degree(a, b, c);
	if (obj.isLimited)
		return (limit(ray, sol, obj));
	return (lowerDist(sol));	

}

double					cylindre(t_object obj, t_ray ray)
{
	double				a;
	double				b;
	double				c;
	t_solution			sol;

	changeReference(&ray, obj);
	a = pow(ray.dir.x, 2) + pow(ray.dir.z, 2);
	b = 2 * (ray.dir.x * ray.o.x + ray.dir.z * ray.o.z);
	c = pow(ray.o.x, 2) + pow(ray.o.z, 2) - pow(obj.radius, 2);
	sol = ft_2nd_degree(a, b, c);
	if (obj.isLimited)
		return (limit(ray, sol, obj));
	return (lowerDist(sol));
}

double					cone(t_object obj, t_ray ray)
{
	double				a;
	double				b;
	double				c;
	t_solution			sol;

	changeReference(&ray, obj);
	a = pow(ray.dir.x, 2) + pow(ray.dir.z, 2) - pow(ray.dir.y * tan(obj.angle), 2);
	b = 2 * (ray.dir.x * ray.o.x + ray.dir.z * ray.o.z - ray.dir.y * tan(obj.angle) * ray.o.y * tan(obj.angle));
	c = pow(ray.o.x, 2) + pow(ray.o.z, 2) - pow(ray.o.y * tan(obj.angle), 2);
	sol = ft_2nd_degree(a, b, c);
	if (obj.isLimited)
		return (limit(ray, sol, obj));
	return (lowerDist(sol));
}
