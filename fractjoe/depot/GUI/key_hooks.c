#include "fractol.h"

void		key_hook_move(t_env *e)
{
	t_cpx	span;

	span.r = (e->mendl.maxX - e->mendl.minX) * 0.01;
	span.i = (e->mendl.maxY - e->mendl.minY) * 0.01;
	if (M_UP == 1) {
		e->mendl.minY += span.i;
		e->mendl.maxY += span.i;
	}
	else if (M_DOWN == 1) {
		e->mendl.minY -= span.i;
		e->mendl.maxY -= span.i;
	}
	else if (M_RIGHT == 1) {
		e->mendl.minX += span.r;
		e->mendl.maxX += span.r;
	}
	else if (M_LEFT == 1) {
		e->mendl.minX -= span.r;
		e->mendl.maxX -= span.r;
	}
}

void		key_hook_zoom(t_env *e)
{
	t_cpx	span;

	span.r = (e->mendl.maxX - e->mendl.minX) * 0.01;
	span.i = (e->mendl.maxY - e->mendl.minY) * 0.01;
	if (M_SIZEP == 1) {
		e->mendl.minX -= span.r;
		e->mendl.maxX += span.r;
		e->mendl.minY -= span.i;
		e->mendl.maxY += span.i;
	}
	else if (M_SIZEM == 1) {
		e->mendl.minX += span.r;
		e->mendl.maxX -= span.r;
		e->mendl.minY += span.i;
		e->mendl.maxY -= span.i;
	}
}
