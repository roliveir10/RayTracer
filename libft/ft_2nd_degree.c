/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2nd_degree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 02:45:29 by roliveir          #+#    #+#             */
/*   Updated: 2019/06/26 09:31:21 by roliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

double			ft_2nd_degree(double a, double b, double c)
{
	double		t1;
	double		t2;
	double		delta;

	if ((delta = pow(b, 2) - 4 * a * c) < 0)
		return (-1);
	t1 = (-b + sqrt(delta)) / (2.0 * a);
	if (!delta)
		return (t1 > 0 ? t1 : -1);
	t2 = (-b - sqrt(delta)) / (2.0 * a);
	if (t1 <= 0 && t2 > 0)
		return (t2);
	if (t1 > 0 && t2 <= 0)
		return (t1);
	return (t1 > t2 ? t2 : t1);
}
