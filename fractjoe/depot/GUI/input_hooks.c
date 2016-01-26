#include <fractol.h>

int			key_press(int keycode, t_env *e)
{
	if (keycode == K_ESC)
		exit(0);
	key_press_on(keycode, e);
	key_press_var(keycode, e);
	key_press_mode(keycode, e);
	key_press_option(keycode, e);
//	ft_putendl(ft_itoa(keycode));
	return (0);
}

int			key_release(int	keycode, t_env *e)
{
	key_release_off(keycode, e);
	return (0);
}

int			motion_hook(int x, int y, t_env *e)
{
	double	nx;
	double	ny;

	if (e->mendl.juliaMod == JMOTION)
	{
		nx = e->mendl.minX + ( e->mendl.maxX - e->mendl.minX ) / WINX * x;
	 	ny = e->mendl.minY + ( e->mendl.maxY - e->mendl.minY ) / WINY * y;
		e->mendl.c.r = nx;
		e->mendl.c.i = ny;
	}
	return(0);
}

int			mouse_hook(int button, int x, int y, t_env *e)
{
	t_cpx	span;
	t_cpx	center;

	span.r = (e->mendl.maxX - e->mendl.minX) * ( 1.0 / e->mendl.zoom);
	span.i = (e->mendl.maxY - e->mendl.minY) * ( 1.0 / e->mendl.zoom);
	center.r = e->mendl.minX + ( e->mendl.maxX - e->mendl.minX ) / WINX * x;
	center.i = e->mendl.minY + ( e->mendl.maxY - e->mendl.minY ) / WINY * y;
	if (button == 4)
	{
		e->mendl.minX = center.r - span.r / 2.0;
		e->mendl.maxX = center.r + span.r / 2.0;
		e->mendl.minY = center.i - span.i / 2.0;
		e->mendl.maxY = center.i + span.i / 2.0;
	}
	else if (button == 5)
	{
		e->mendl.minX = center.r - span.r * 2.0;
		e->mendl.maxX = center.r + span.r * 2.0;
		e->mendl.minY = center.i - span.i * 2.0;
		e->mendl.maxY = center.i + span.i * 2.0;
	}
	return (0);
}

int			loop_hook(t_env *e)
{
	key_hook_move(e);
	key_hook_zoom(e);
	drawFract(e);
	expose_hook(e);
	return (0);
}
