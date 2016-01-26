#include "fractol.h"

void		key_press_on(int keycode, t_env *e)
{
	if (keycode == K_UP)
		M_UP = 1;
	else if (keycode == K_DOWN)
		M_DOWN = 1;
	else if (keycode == K_LEFT)
		M_LEFT = 1;
	else if (keycode == K_RIGHT)
		M_RIGHT = 1;
	else if (keycode == K_SIZEP)
		M_SIZEP = 1;
	else if (keycode == K_SIZEM)
		M_SIZEM = 1;
}

void		key_release_off(int keycode, t_env *e)
{
	if (keycode == K_UP)
		M_UP = 0;
	else if (keycode == K_DOWN)
		M_DOWN = 0;
	else if (keycode == K_LEFT)
		M_LEFT = 0;
	else if (keycode == K_RIGHT)
		M_RIGHT = 0;
	if (keycode == K_SIZEP)
		M_SIZEP = 0;
	else if (keycode == K_SIZEM)
		M_SIZEM = 0;
}

void		key_press_option(int keycode, t_env *e)
{
	if (keycode == K_KONE)
		e->fractOpt = MENDELBROT;
	else if (keycode == K_KTWO)
		e->fractOpt = JULIA;
	else if (keycode == K_KTHREE)
		e->fractOpt = SQUAREINF;
	else if (keycode == K_KFOUR)
		e->fractOpt = ANIME;
	else if (keycode == K_KEQUAL)
		e->mendl.eqInd = (e->mendl.eqInd + 1) % NBEQ;
	else if (keycode == K_KDASH)
		e->mendl.cpxInd = (e->mendl.cpxInd + 1) % NBIMGS;
	else if (keycode == K_KBRAK)
		e->mendl.colInd = (e->mendl.colInd + 1) % NBCOL;
	else if (keycode == K_SAVEST)
		showStat(e);
	else if (keycode == K_RESET)
		reset_var(e);
}

void		key_press_mode(int keycode, t_env *e)
{
	if (keycode == K_KSHIFT)
	{
		if (e->mendl.juliaMod == JFIXED)
			e->mendl.juliaMod = JMOTION;
		else
			e->mendl.juliaMod = JFIXED;
	}
	else if (keycode == K_KSPACE)
	{
		set_cpx(&e->fn_array.img[NBIMGS - 1], e->mendl.c.r, e->mendl.c.i);
		e->mendl.juliaMod = JFIXED;
		e->mendl.cpxInd = NBIMGS - 1;
	}
}

void		key_press_var(int keycode, t_env *e)
{
	if (keycode == K_PLUS)
		e->mendl.nbIt += 10;
	else if (keycode == K_MINUS)
	{
		if (e->mendl.nbIt > 15)
			e->mendl.nbIt -= 10;
	}
	else if (keycode == K_BPLUS)
		e->mendl.borne += 20;
	else if (keycode == K_BMINUS)
	{
		if (e->mendl.borne > 0)
			e->mendl.borne -= 20;
	}
	else if (keycode == K_ZOOMP)
			e->mendl.zoom++;
	else if (keycode == K_ZOOMM)
	{
		if (e->mendl.zoom > 2)
			e->mendl.zoom--;
	}
}
