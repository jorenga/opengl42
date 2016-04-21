#include "matrix.h"

void					print_matx(float *m)
{
	printf("%f\t%f\t%f\t%f\n", m[0], m[4], m[8], m[12]);
	printf("%f\t%f\t%f\t%f\n", m[1], m[5], m[9], m[13]);
	printf("%f\t%f\t%f\t%f\n", m[2], m[6], m[10], m[14]);
	printf("%f\t%f\t%f\t%f\n", m[3], m[7], m[11], m[15]);
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
