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
	int				key[NBR_KEY] = {KESCAP};
	void			(*function[NBR_KEY])(int) = {escap};
	int				i = -1;

	while (++i < NBR_KEY)
		if (key[i] == keycode)
			function[i](keycode);
	return (1);
}

int					mousePress(int keycode, __unused int x, __unused int y)
{
	if (keycode == MDOWN || keycode == MUP)
		moveCamZ(keycode);
	return (1);
}
