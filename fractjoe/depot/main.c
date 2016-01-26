
#include "fractol.h"

void			reset_var(t_env *e)
{
	e->mendl.minX = -2.4;
	e->mendl.maxX = 2.4;
	e->mendl.minY = -1.5;
	e->mendl.maxY = 1.5;
}

int				ft_usage( void )
{
	ft_putendl("Bad usage.\nChoose one of the following fractal:");
	ft_putendl("\t\tjulia\n\t\tmendelbrot\n\t\tcarpet\n\t\tauto");
	return (0);
}

int				check_param(t_env *e, int ac, char **av  )
{
	if (ac != 2)
		return (ft_usage());
	if (!ft_strcmp(av[1], "julia"))
		e->fractOpt = JULIA;
	else if (!ft_strcmp(av[1], "mendelbrot"))
		e->fractOpt = MENDELBROT;
	else if (!ft_strcmp(av[1], "carpet"))
		e->fractOpt = SQUAREINF;
	else if (!ft_strcmp(av[1], "auto"))
		e->fractOpt = JULIA;
	else
		return (ft_usage());
	return (1);
}

int				main( int ac, char **av )
{
	t_env		e;

	if (!check_param(&e, ac, av))
		return (0);
	print_info();
	init_env(&e);
	init_mlx(&e);
	init_mendel(&e);
	mlx_input(&e);
	mlx_system(&e);
	return (0);
}
