#include "rt.h"

/*int					keyPress(int keycode)
{
	int				key[NBR_KEY] = {KESCAP};
	void			(*function[NBR_KEY])(int) = {escap};
	int				i = -1;

	while (++i < NBR_KEY)
		if (key[i] == keycode)
			function[i](keycode);
	return (1);
}
*/

void				keyHandler(SDL_Event *event)
{
	if (event->type == SDL_MOUSEBUTTONDOWN)
		return ;
	else if (event->type == SDL_MOUSEWHEEL)
		return ;
	else if (event->type == SDL_KEYDOWN)
		return ;
	else if (event->type == SDL_KEYUP)
		return ;
}
