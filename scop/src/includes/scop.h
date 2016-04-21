#ifndef SCOP_H
# define SCOP_H

# include "gl_include.h"
# include "gl_struct.h"
# include "gl_context.h"
# include "obj_import.h"
# include "bmp_import.h"
# include "matrix.h"
# include "shader.h"

void	setup_param(t_win_info* info, char* name, GLfloat width,
						GLfloat height);
void	setup_clip(t_clip_info* clip, GLfloat aspect);
int		error(char *err);
void	init_input(t_gl_data *data);
void	move_mesh(t_gl_data *data, t_mesh *mesh, float *m, float *al);

#endif
