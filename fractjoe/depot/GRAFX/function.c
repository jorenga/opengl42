
#include <fractol.h>

void			transform_cpx(t_env *e, t_cpx *c, t_world *w)
{
	w->x = (int) (( (c->r + e->mendl.maxX) / (e->mendl.maxX ) ) * WINX/2);
	w->y = (int) (( ((c->i + e->mendl.maxY) / (e->mendl.maxY )) ) * WINY/2);
}

void			clean_screen(t_env *e)
{
	int		i;
	int		j;
	t_rgb	col;
	init_color(&col, 0, 0, 0);
	for (i = 0 ; i < WINX ; i++)
	{
		for (j = 0; j < WINY ; j++)
		{
			putPixel(e, &col, i, j);
		}
	}
}

void		spiro(t_env *e)
{
	int		i;
	int		points;
	double	mod_inc = 1.5 / 1000000;
	double	arg_inc = M_PI / 100;
	t_rgb	rgb;
	t_cpx	c;
	t_world	w;

	i = 0;
	points = 1000000;
	set_polar_cpx(&c, 0, 0);
	init_color(&rgb, 0xFF, 0xFF, 0xFF);
	clean_screen(e);
	while (i < points)
	{
		set_polar_cpx(&c, (c.mod + mod_inc), (c.arg + arg_inc));
		polar_to_coord_cpx(&c);
		transform_cpx(e, &c, &w);
		put_world_cpx(e, &rgb, &w);
		i++;
	}
}
