#include <fractol.h>

void			putPixel(t_env *e, void* color, int x, int y)
{
	char		*tmp;

	tmp = DATA + (LINESIZE * y) + (x * (BPP / 8));
	ft_memcpy(tmp, color, 3);
}

void			put_world_cpx(t_env *e, void *col, t_world *w)
{
	char		*tmp;

	tmp = DATA + (LINESIZE * w->y) + (w->x * (BPP / 8));
	ft_memcpy(tmp, col, 3);
}

void			printMendlVar(t_env *e, unsigned long int t)
{
	printf("=============================\n");
	printf("spf: %lum%lus%lums%luus\n",
		   	t / 60000000, (t / 1000000) % 60, (t / 1000) % 1000, t % 1000);
	printf("nbIt: %d\tborne: %d\n", e->mendl.nbIt, e->mendl.borne);
	printf("magn: x%f\n", 4.8 / (e->mendl.maxX - e->mendl.minX));
	printf("zoom: x%f\n", e->mendl.zoom);
}

void			showStat(t_env *e)
{
	printMendlVar(e, e->inter);
}

void			print_info( void )
{
	ft_putendl("INFO\nChange fractal: 1:mendel\t2:julia\t\t3:carpet\t4:animation");
	ft_putendl("Change mode:\tSHIFT");
	ft_putendl("Pause:\t\tSPACE");
	ft_putendl("Change images: -\tChange equation: =\tChange colors: [");
	ft_putendl("Change nb iteration: +: / -: .\tChange borne +: m -: n");
	ft_putendl("Zoom: +: k -: l");
	ft_putendl("Show stats: s");
}
