
#include <pthread.h>
#include "fractol.h"

void			create_thread(t_env *e, void*(*fn)(void*))
{
	int			i;
	int			nb_lines;
	int			nb_thread;
	pthread_t	*thread_pool;
	t_thread	*thread_data;

	i = 0;
	nb_thread = sysconf(_SC_NPROCESSORS_ONLN);
	if ((thread_pool = (pthread_t *)malloc(sizeof(pthread_t) * nb_thread)) == NULL)
		exit(0);
	if ((thread_data = (t_thread *)malloc(sizeof(t_thread) * nb_thread)) == NULL)
		exit(0);
	nb_lines = WINX / nb_thread;
	while (i < nb_thread)
	{
		thread_data[i].th_start = i * nb_lines;
		thread_data[i].th_stop = (i + 1) * nb_lines;
		thread_data[i].e = e;
		pthread_create(thread_pool + i, NULL, fn, thread_data + i);
		i++;
	}
	i = 0;
	while (i < nb_thread)
		pthread_join(thread_pool[i++], NULL);
	free(thread_pool);
}

void			julia_animation(t_env *e)
{
	int		i;
	int		points;
	double	mod_inc = 1.5 / 1000;
	double	arg_inc = M_PI / 100;
	unsigned long int t;
	unsigned long int ts;
	unsigned long int te;

	i = 0;
	points = 1000;
	e->fractOpt = JULIA;
	e->mendl.juliaMod = JMOTION;
	reset_var(e);
	ts = getTime();
	while (i < points)
	{
		set_polar_cpx(&e->mendl.c, i * mod_inc, i * arg_inc);
		polar_to_coord_cpx(&e->mendl.c);
		create_thread(e, drawingLoop);
		expose_hook(e);
		i++;
	}
	te = getTime();
	t = te - ts;
	printf("animation: %lum%lus%lums%luus\n", t / 60000000, (t / 1000000) % 60, (t / 1000) % 1000, t % 1000);
}
