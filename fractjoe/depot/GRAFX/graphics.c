#include <fractol.h>

void			drawFract(t_env *e)
{
	unsigned long int time;

	time = getTime();
	if (e->fractOpt == JULIA || e->fractOpt == MENDELBROT)
	{
		create_thread(e, drawingLoop);
	}
	else if (e->fractOpt == SQUAREINF)
	{
		create_thread(e, newDraw);
	}
	else if (e->fractOpt == ANIME)
	{
		julia_animation(e);
	}
	e->inter = time - e->time;
	e->time = time;
}

int				iterMaster(t_env *e, t_cpx C, t_cpx Z)
{
	int			a;

	a = 0;
	while (a < e->mendl.nbIt)
	{
		e->fn_array.eq[e->mendl.eqInd](&C, &Z);
		if ( (Z.r * Z.r + Z.i * Z.i) >= e->mendl.borne )
			break;
		a++;
	}
	return (a);
}

void			init_fractal(t_env *e, t_fractal *f, int x, int y)
{
	f->z.r = e->mendl.minX + ( e->mendl.maxX - e->mendl.minX ) / WINX * x;
	f->z.i = e->mendl.minY + ( e->mendl.maxY - e->mendl.minY ) / WINY * y;
	if (e->mendl.juliaMod == JFIXED)
		copy_cpx(&f->c, &e->fn_array.img[e->mendl.cpxInd]);
	else
		copy_cpx(&f->c, &e->mendl.c);
}

void			*drawingLoop(void *thread_data)
{
	int			a;
	double		x;
	double		y;
	t_rgb		col;
	t_env		*e;
	t_thread	*data;
	t_fractal	f;

	data = thread_data;
	e = data->e;
	x = data->th_start;
	while (x < data->th_stop)
	{
		y = 0;
		while (y < WINY)
		{
			init_fractal(e, &f, x, y);
			if (e->fractOpt == MENDELBROT)
				a = iterMaster(e, f.z, f.c);
			else if (e->fractOpt == JULIA)
				a = iterMaster(e, f.c, f.z);
			create_color(e, a, &col);
			putPixel(e, &col, x, y);
			y++;
		}
		x++;
	}
	return NULL;
}

void			*newDraw(void *thread_data)
{
	int			a;
	int			x;
	int			y;
	t_rgb		col;
	t_env		*e;
	t_thread	*data;

	data = thread_data;
	e = data->e;
	x = data->th_start;
	while (x < data->th_stop)
	{
		y = 0;
		while (y < WINY)
		{
			a = carpet(x, y);
			create_color(e, a, &col);
			putPixel(e, &col, x, y);
			y++;
		}
		x++;
	}
	return (NULL);
}
