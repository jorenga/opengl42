#include "scop.h"

void	setup_param(t_win_info* info, char* name, GLfloat width, GLfloat height)
{
	info->name = name;
	info->width = width;
	info->height = height;
}

void	setup_clip(t_clip_info* clip, GLfloat aspect)
{
	clip->fov = 45;
	clip->aspect = aspect;
	clip->z_near = 0.1;
	clip->z_far = 1000;
}

int		error(char *err)
{
	ft_putendl(err);
	return (1);
}

void	init_input(t_gl_data *data)
{
	data->input.x = 0;
	data->input.y = 0;
	data->input.z = 0;
	data->input.col = 1;
	data->input.anim = 1;
}

void	move_mesh(t_gl_data *data, t_mesh *mesh, float *m, float *al)
{
	mesh->pos.x += data->input.x;
	mesh->pos.y += data->input.y;
	mesh->pos.z += data->input.z;
	get_identity_matx(m);
	translate_matx(m, mesh->pos.x, mesh->pos.y, mesh->pos.z);
	rot_y_matx(m, *al);
	translate_matx(m, mesh->center.x * -1, mesh->center.y * -1,
			mesh->center.z * -1);
	*al += 0.01;
	if (data->input.col == 1 && data->input.anim < 1)
		data->input.anim += 0.01;
	if (data->input.col == -1 && data->input.anim > 0)
		data->input.anim -= 0.01;
	if (data->input.anim > 1)
		data->input.anim = 1;
	if (data->input.anim < 0)
		data->input.anim = 0;
}
