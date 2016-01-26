
#include "fractol.h"

void			init_imgArray(t_cpx img[NBIMGS])
{
	set_cpx(&img[0], -0.4, 0.6);
	set_cpx(&img[1], 0.285, 0.01);
	set_cpx(&img[2], 0.8, 0.156);
	set_cpx(&img[3], 0.279, 0.0);
	set_cpx(&img[4], -0.65, 0.0);
	set_cpx(&img[5], 0.059, 0.0);
	set_cpx(&img[6], 0.04, 0.0);
	set_cpx(&img[7], 0.0, 0.0);
}

void			init_eqArray(void(*eqArray[NBEQ])(t_cpx*,t_cpx*))
{
	eqArray[0] = squareCpx;
	eqArray[1] = cubeCpx;
	eqArray[2] = expCpx;
	eqArray[3] = expZCpx;
	eqArray[4] = exp2Cpx;
}

void			init_colArray(void(*col[NBCOL])(t_env*, int, t_rgb*))
{
	col[0] = fn0_grad;
	col[1] = fn1_grad;
	col[2] = fn2_grad;
	col[3] = fn3_grad;
	col[4] = fn4_grad;
}

void			init_mendel(t_env *e)
{
	e->mendl.nbIt = 100;
	e->mendl.borne = 100;
	e->mendl.minX = -2.4;
	e->mendl.maxX = 2.4;
	e->mendl.minY = -1.5;
	e->mendl.maxY = 1.5;
	e->mendl.zoom = 2.0;
	e->mendl.eqInd = 0;
	e->mendl.cpxInd = 0;
	e->mendl.colInd = 0;
	e->mendl.juliaMod = JMOTION;
}

void			init_env(t_env *e)
{
	WINX = 600;
	WINY = 400;
	e->time = getTime();
	e->inter = 0;
	init_eqArray(e->fn_array.eq);
	init_imgArray(e->fn_array.img);
	init_colArray(e->fn_array.col);
}
