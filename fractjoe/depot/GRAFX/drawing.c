#include <fractol.h>

double			ftmod(double x, double mod)
{
	if (x >= mod)
		x = 0;
	return (x);
}

double		ftabs(double x)
{
	if (x > 0)
		return (x);
	return (-x);
}

int				carpet(int ox, int oy)
{
	int			a;
	int			mod;
	int			x = ox - 300;
	int			y = oy - 200;

	x  = x > 0 ? x : -x;
	y  = y > 0 ? y : -y;
	a = 0;
	mod = 3;
	while (x > 0 || y > 0)
	{
		if (((x % mod) == 1) && ((y % mod) == 1))
			return (0);
		x /= mod;
		y /= mod;
		a++;
	}
	a = a > 0 ? 10 : 0;
	return (a);

}

unsigned long int	getTime( void )
{
	unsigned long int	time;
	struct timeval	tp;

	gettimeofday(&tp, NULL);

	time = tp.tv_usec;
	time += tp.tv_sec * 1000000;

	return (time);
}
