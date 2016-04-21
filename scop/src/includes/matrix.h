#ifndef MATRIX_H
# define MATRIX_H

# include <math.h>
# include <stdio.h>
# include "gl_struct.h"
# include "libft.h"

void			print_matx(float *m);
void			mult_matx(float *m1, float *m2);
void			get_identity_matx(float *m);
void			get_proj_matx(float *m, t_clip_info *clip);
void			translate_matx(float *m, float x, float y, float z);
void			rot_x_matx(float *m, float alpha);
void			rot_y_matx(float *m, float alpha);
void			rot_z_matx(float *m, float alpha);

#endif
