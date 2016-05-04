__kernel void	init(__global float4 *particles)
{
	const int	i = get_global_id(0);
//	printf("kernel[%d]", i);
if (i  >= 1000)
	return ;
	float		x, y, z, w;

	x = i % 10 - 5.0f;
	y = int(i / 100.0f) - 5.0f;
	z = int((i % 100) / 10.0f) - 5.0f;
	w = 1.0f;

	particles[i] = (float4) (x, y, z, w);
//	printf("%f   %f   %f   %f\n", particles[i].x, particles[i].y, particles[i].z, particles[i].w);
}
