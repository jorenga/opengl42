#include <fractol.h>

//			Z = Z^2 + C
void			squareCpx(t_cpx *C, t_cpx *Z)
{
	double		r;
	double		i;

	r = Z->r;
	i = Z->i;
	Z->r = r * r - i * i + C->r;
	Z->i = 2 * r * i + C->i;
}

//			Z = Z^3 + C
void			cubeCpx(t_cpx *C, t_cpx *Z)
{
	double		r;
	double		i;

	r = Z->r;
	i = Z->i;
	Z->r = r * r * r - 3 * r * i * i + C->r;
	Z->i = 3 * r * r * i - i * i * i + C->i;
}

//			Z = exp(Z) + C
void			expCpx(t_cpx *C, t_cpx *Z)
{
	double		r;
	double		i;

	r = Z->r;
	i = Z->i;
	Z->r = exp(r) * cos(i) + C->r;
	Z->i = exp(r) * sin(i) + C->i;
}

//			Z = exp(Z) * Z + C
void			expZCpx(t_cpx *C, t_cpx *Z)
{
	double		r;
	double		i;

	r = Z->r;
	i = Z->i;
	Z->r = r * exp(r) * cos(i) - i * exp(r) * sin(i) + C->r;
	Z->i = i * exp(r) * cos(i) + r * exp(r) * sin(i) + C->i;
}

//			Z = exp(Z^2) * Z + C
void			exp2Cpx(t_cpx *C, t_cpx *Z)
{
	double		r;
	double		i;

	r = Z->r;
	i = Z->i;
	Z->r = exp(r*r) / exp(i*i) * cos(2 * r * i) + C->r;
	Z->i = exp(r*r) / exp(i*i) * sin(2 * r * i) + C->i;
}
