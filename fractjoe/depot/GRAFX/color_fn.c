
#include <fractol.h>

void				fn0_grad(t_env *e, int a, t_rgb *c)
{
	c->b = ( 1.0 / (double) a ) * 255;
	c->r = a * 255 / e->mendl.nbIt;
	c->g = 0;
}

void				fn1_grad(t_env *e, int a, t_rgb *c)
{
	(void)e;
	c->r = (1 - cos(a)) * (255 / 2);
	c->g = (cos(a) + 1) * (255 / 2);
	c->b = (1 - sin(a)) * (255 / 2);
}

void				fn2_grad(t_env *e, int a, t_rgb *c)
{
	double			x;

	x = (double)a / (double)e->mendl.nbIt;
	c->r = (1 - pow((1.0 - x), (1.0 / 2.0))) * 255;
	c->g = (1 - pow((1.0 - x), (1.0 / 3.0))) * 255;
	c->b = pow(x, 2) * 255;
}

void				fn3_grad(t_env *e, int a, t_rgb *c)
{
	double			x;

	(void)e;
	x = (double)a / (double)e->mendl.nbIt;
	c->r = x * 255;
	c->g = x * 255;
	c->b = x * 255;
}

void				fn4_grad(t_env *e, int a, t_rgb *c)
{
	double			x;
	double			f_r;
	double			f_g;
	double			f_b;
	double			max;

	x = (double)a / (double)e->mendl.nbIt;
	if (x <= 0.0 || x >= 1.0)
	{
		init_color(c, 0, 0, 0);
		return ;
	}
	f_r = ft_max( 0.0, (x < 0.5) ? cos(x * 1.5 * M_PI) : -sin(x * 1.5 * M_PI) );
	f_g = ft_max( 0.0, sin(x * 1.5 * M_PI) );
	f_b = ft_max( 0.0, -cos(x * 1.5 * M_PI) );
	max = ft_max( f_r, ft_max(f_g, f_b) );
	if (max == 0.0)
	{
		init_color(c, 0, 0, 0);
		return ;
	}
	init_color(c, (f_r / max) * 255, (f_g / max) * 255, (f_b / max) * 255);
}
