#include "rt.h"

void				escap(int keycode)
{
	(void)keycode;
	delenv();
}

int					rt_close(void)
{
	delenv();
	return (1);
}

int					keyPress(int keycode)
{
	const int		key[NBR_KEY] = {KESCAP};
	static void		(*function[NBR_KEY])(int) = {escap};
	int				i = -1;

	while (++i < NBR_KEY)
		if (key[i] == keycode)
			function[i](keycode);
	return (1);
}
