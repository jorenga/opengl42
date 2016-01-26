#include "fractol.h"

void			init_mlx(t_env *e)
{
	MLX = mlx_init();
	WIN = mlx_new_window(MLX, WINX, WINY, "my fractal world");
	IMG = mlx_new_image(MLX, WINX, WINY);
	DATA = mlx_get_data_addr(IMG, &BPP, &LINESIZE, &END);
}

void			mlx_input(t_env *e)
{
	mlx_do_key_autorepeatoff(MLX);
	mlx_hook(WIN, KEYPRESS, KEYPRESSMASK, key_press, e);
	mlx_hook(WIN, KEYRELEASE, KEYRELEASEMASK, key_release, e);
	mlx_hook(WIN, PTRMOTION, PTRMOTIONMASK, motion_hook, e);
	mlx_mouse_hook(WIN, mouse_hook, e);
}

void			mlx_system(t_env *e)
{
	mlx_loop_hook(MLX, loop_hook, e);
	mlx_expose_hook(WIN, expose_hook, e);
	mlx_loop(MLX);
}

int				expose_hook(t_env *e)
{
	mlx_put_image_to_window( MLX, WIN, IMG, 0, 0 );
	return(0);
}
