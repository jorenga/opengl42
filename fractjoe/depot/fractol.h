#ifndef FRACTOL_H
# define FRACTOL_H

# include <sys/time.h>
# include <stdio.h>
# include <libft.h>
# include <math.h>
# include <pthread.h>
# include "mlx.h"

# define PHI				1.6180339887

# define ABS(x)				(x < 0) ? -x : x

# define MENDELBROT			0
# define JULIA				1
# define SQUAREINF			2
# define ANIME				3

# define JMOTION			0
# define JFIXED				1

# define NBIMGS				8
# define NBEQ				5
# define NBCOL				5

# define MLX				e->mlx
# define WIN				e->win
# define IMG				e->img
# define DATA				e->imgData
# define LINESIZE			e->lineSize
# define BPP				e->bpp
# define END				e->endiannes
# define WINX				e->winX
# define WINY				e->winY
/* 3:2 */

# define KEYPRESS			2
# define KEYRELEASE			3
# define PTRMOTION			6
# define KEYPRESSMASK		(1L<<0)
# define KEYRELEASEMASK		(1L<<1)
# define PTRMOTIONMASK		(1L<<6)

# define K_ESC				65307		/* KEY <ESC> */
# define K_UP				65362		/* KEY <UP> */
# define K_DOWN				65364		/* KEY <DOWN> */
# define K_RIGHT			65361		/* KEY <RIGHT> */
# define K_LEFT				65363		/* KEY <LEFt> */
# define K_PLUS				47			/* KEY </> */
# define K_MINUS			46			/* KEY <.> */
# define K_BPLUS			109			/* KEY <M> */
# define K_BMINUS			110			/* KEY <N> */
# define K_SIZEP			108			/* KEY <L> */
# define K_SIZEM			107			/* KEY <K> */
# define K_ZOOMP			120			/* KEY <X> */
# define K_ZOOMM			122			/* KEY <Z> */
# define K_SAVEST			115			/* KEY <S> */
# define K_RESET			114			/* KEY <R> */
# define K_KONE				49			/* KEY <1> */
# define K_KTWO				50			/* KEY <2> */
# define K_KTHREE			51			/* KEY <3> */
# define K_KFOUR			52			/* KEY <4> */
# define K_KFIVE			53			/* KEY <5> */
# define K_KEQUAL			61			/* KEY <=> */
# define K_KDASH			45			/* KEY <-> */
# define K_KBRAK			91			/* KEY <[> */
# define K_KBS				92			/* KEY <BACKSPACE> */
# define K_KSPACE			32			/* KEY <SPACE> */
# define K_KSHIFT			65506		/* KEY <SHIFT> */

# define M_UP				e->keys.k_up
# define M_DOWN				e->keys.k_down
# define M_LEFT				e->keys.k_left
# define M_RIGHT			e->keys.k_right
# define M_SIZEP			e->keys.k_sizep
# define M_SIZEM			e->keys.k_sizem
# define M_ZOOMP			e->keys.k_zoomp
# define M_ZOOMM			e->keys.k_zoomm

typedef struct				s_env t_env;

typedef struct				s_rgb
{
	char					b;
	char					g;
	char					r;
}							t_rgb;

typedef struct				s_cpx
{
	double					r;
	double					i;
	double					mod;
	double					arg;
}							t_cpx;

typedef struct				s_world
{
	int						x;
	int						y;
}							t_world;

typedef struct				s_keys
{
	int						k_up;
	int						k_down;
	int						k_left;
	int						k_right;
	int						k_sizep;
	int						k_sizem;
	int						k_zoomp;
	int						k_zoomm;
}							t_keys;

typedef struct				s_mendlVar
{
	int						nbIt;
	int						borne;
	double					minX;
	double					maxX;
	double					minY;
	double					maxY;
	double					zoom;
	t_cpx					c;
	int						eqInd;
	int						cpxInd;
	int						colInd;
	char					juliaMod;
}							t_mendlVar;

typedef struct				s_fnArray
{
	t_cpx					img[NBIMGS];
	void(*eq[NBEQ])(t_cpx*, t_cpx*);
	void(*col[NBCOL])(t_env*, int, t_rgb*);
}							t_fnArray;

typedef struct				s_fractal
{
	t_cpx					c;
	t_cpx					z;
}							t_fractal;

struct						s_env
{
	void					*mlx;
	void					*win;
	void					*img;
	char					*imgData;
	int						lineSize;
	int						bpp;
	int						endiannes;
	int						winX;
	int						winY;
	t_mendlVar				mendl;
	t_keys					keys;
	t_fnArray				fn_array;
	char					fractOpt;
	unsigned long int	 	time;
	unsigned long int		inter;
};

typedef struct				s_thread
{
	int						th_start;
	int						th_stop;
	t_env					*e;
}							t_thread;

/*
void				test_color(t_env *e, int a, t_rgb *c);
void*						drawingLoop(void *thread_data);
void*						newDraw(void *thread_data);
void			set_polar_cpx(t_cpx *c, double mod, double arg);
void			polar_to_coord_cpx(t_cpx *c);
void			julia_animation(t_env *e);
void		spiro(t_env *e);
void			create_thread(t_env *e, void*(*fn)(void*));
*/

/* MLX_FUNCTION.C */

void						init_mlx(t_env *e);
void						mlx_input(t_env *e);
void						mlx_system(t_env *e);
int							expose_hook(t_env *e);


/* INIT.C */

void						init_imgArray(t_cpx img[NBIMGS]);
void						init_eqArray(void(*eqArray[NBEQ])(t_cpx*,t_cpx*));
void						init_colArray(void(*col[NBCOL])(t_env*, int, t_rgb*));
void						init_mendel(t_env *e);
void						init_env(t_env *e);


/* MAIN.C */

void						reset_var(t_env *e);
int							ft_usage( void );
int							check_param(t_env *e, int ac, char **av  );


/* GUI/INPUT_HOOKS.C */

int							loop_hook(t_env *e);
int							mouse_hook(int button, int x, int y, t_env *e);
int							motion_hook(int x, int y, t_env *e);
int							key_press(int keycode, t_env *e);
int							key_release(int	keycode, t_env *e);


/* GUI/KEY_INPUT.C */

void						key_press_on(int keycode, t_env *e);
void						key_release_off(int keycode, t_env *e);
void						key_press_var(int keycode, t_env *e);
void						key_press_mode(int keycode, t_env *e);
void						key_press_option(int keycode, t_env *e);


/* GUI/KEY_HOOKS.C */

void						key_hook_move(t_env *e);
void						key_hook_zoom(t_env *e);


/* GRAFX/GRAPHICS.C */

void						drawFract(t_env *e);
int							iterMaster(t_env *e, t_cpx C, t_cpx Z);
void						init_fractal(t_env *e, t_fractal *f, int x, int y);
void						*drawingLoop(void *thread_data);
void						*newDraw(void *thread_data);

/* GRAFX/COMPLEX.C */

void						set_cpx(t_cpx *c, double r, double i);
void						copy_cpx(t_cpx *a, t_cpx *b);
void						set_polar_cpx(t_cpx *c, double mod, double arg);
void						coord_to_polar_cpx(t_cpx *c);
void						polar_to_coord_cpx(t_cpx *c);

/* GRAFX/FUNCTION.C */

void						transform_cpx(t_env *e, t_cpx *c, t_world *w);
void						clean_screen(t_env *e);
void						spiro(t_env *e);


/* GRAFX/EQUATIONS.C */

void						squareCpx(t_cpx *C, t_cpx *Z);
void						cubeCpx(t_cpx *C, t_cpx *Z);
void						expCpx(t_cpx *C, t_cpx *Z);
void						expZCpx(t_cpx *C, t_cpx *Z);
void						exp2Cpx(t_cpx *C, t_cpx *Z);


/* GRAFX/COLOR.C */

double						ft_max(double a, double b);
void						init_color(t_rgb *c, int r, int g, int b);
void						create_color( t_env *e, int a, t_rgb *c);


/* GRAFX/COLOR_FN.C */

void						fn0_grad(t_env *e, int a, t_rgb *c);
void						fn1_grad(t_env *e, int a, t_rgb *c);
void						fn2_grad(t_env *e, int a, t_rgb *c);
void						fn3_grad(t_env *e, int a, t_rgb *c);
void						fn4_grad(t_env *e, int a, t_rgb *c);


/* GRAFX/DISPLAY.C */

void						putPixel(t_env *e, void* color, int x, int y);
void						put_world_cpx(t_env *e, void* color, t_world *w);
void						printMendlVar(t_env *e, unsigned long int fTime);
void						showStat(t_env *e);
void						print_info( void );


/* GRAFX/DRAWING.C */

int							carpet(int x, int y);
double						ftmod(double x, double mod);
double						ftabs(double x);
unsigned long int			getTime(void);


/* GRAFX/THREAD.C */

void						create_thread(t_env *e, void*(*fn)(void*));
void						julia_animation(t_env *e);


#endif
