#include "matrix.h"

void			rot_x_matx(float *m, float alpha)
{
	float		r[16];

	get_identity_matx(r);
	r[5]  =  cos(alpha);
	r[6]  =  sin(alpha);
	r[9]  = -sin(alpha);
	r[10] =  cos(alpha);
	mult_matx(m, r);
}

void			rot_y_matx(float *m, float alpha)
{
	float		r[16];

	get_identity_matx(r);
	r[0]  =  cos(alpha);
	r[2]  = -sin(alpha);
	r[8]  =  sin(alpha);
	r[10] =  cos(alpha);
	mult_matx(m, r);
}

void			rot_z_matx(float *m, float alpha)
{
	float		r[16];

	get_identity_matx(r);
	r[0]  =  cos(alpha);
	r[1]  =  sin(alpha);
	r[4]  = -sin(alpha);
	r[5]  =  cos(alpha);
	mult_matx(m, r);
}

void			translate_matx(float *m, float x, float y, float z)
{
	float		t[16];

	get_identity_matx(t);
	t[12] = x;
	t[13] = y;
	t[14] = z;
	mult_matx(m, t);
}
