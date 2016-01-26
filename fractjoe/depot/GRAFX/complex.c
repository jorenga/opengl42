
#include <fractol.h>

void			set_cpx(t_cpx *c, double r, double i)
{
	c->r = r;
	c->i = i;
}

void			set_polar_cpx(t_cpx *c, double mod, double arg)
{
	c->mod = mod;
	c->arg = arg;
}

void			copy_cpx(t_cpx *a, t_cpx *b)
{
	a->r = b->r;
	a->i = b->i;
}

void			coord_to_polar_cpx(t_cpx *c)
{
	c->mod = sqrt(c->r * c->r + c->i * c->i);
	c->arg = atan(c->i / c->r);
}

void			polar_to_coord_cpx(t_cpx *c)
{
	c->r = c->mod * cos(c->arg);
	c->i = c->mod * sin(c->arg);
}
