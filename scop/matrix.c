#include "matrix.h"

void					print_matx(float *m)
{
	printf("%f\t%f\t%f\t%f\n", m[0], m[4], m[8], m[12]);
	printf("%f\t%f\t%f\t%f\n", m[1], m[5], m[9], m[13]);
	printf("%f\t%f\t%f\t%f\n", m[2], m[6], m[10], m[14]);
	printf("%f\t%f\t%f\t%f\n", m[3], m[7], m[11], m[15]);
}

void					copy_matx(float *m1, float *m2)
{
	int					i;

	i = 0;
	while (i < 16)
	{
		m1[i] = m2[i];
		i++;
	}
}

void					mult_matx(float *m1, float *m2)
{
	float		t[16];

	t[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	t[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	t[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	t[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];
	t[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	t[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	t[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	t[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];
	t[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	t[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	t[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	t[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];
	t[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	t[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	t[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	t[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];
	copy_matx(m1, t);
}

void			get_identity_matx(float *m)
{
	ft_bzero(m, sizeof(float) * 16);
	m[0] = 1;
	m[5] = 1;
	m[10] = 1;
	m[15] = 1;
}

void			get_proj_matx(float *m, t_clip_info *clip)
{
	float		f;

	ft_bzero(m, sizeof(float) * 16);
	f = 1.0f / tanf(clip->fov / 2.0f);
	m[0] = f / clip->aspect;
	m[5] = f;
	m[10] = (clip->z_near + clip->z_far) / (clip->z_near - clip->z_far);
	m[11] = -1.0;
	m[14] = 2.0 * (clip->z_near * clip->z_far) / (clip->z_near - clip->z_far);
	m[15] = 0.0;
}

void			rot_y_matx(float *m, float alpha)
{
	float		r[16];

	get_identity_matx(r);
	r[0] = cos(alpha);
	r[2] = -sin(alpha);
	r[8] = sin(alpha);
	r[10] = cos(alpha);
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
