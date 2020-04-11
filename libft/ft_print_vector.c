#include "libft.h"

void			ft_print_vector(t_vector vector)
{
	ft_putnbr(vector.x);
	ft_putchar(' ');
	ft_putnbr(vector.y);
	ft_putchar(' ');
	ft_putendlnb(vector.z);
}
