
#include <fractol.h>

double				ft_max(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}

void				init_color(t_rgb *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void				create_color(t_env *e, int a, t_rgb *c)
{
	e->fn_array.col[e->mendl.colInd](e, a, c);
}
