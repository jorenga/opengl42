__kernel void	init(__global float4 *particles)
{
	const int	i = get_global_id(0);
	float		x, y, z;

	x = i % 10 - 5.0f;
	y = i / 100.0f - 5.0f;
	z = (i % 100) / 10.0f - 5.0f;

	particles[i].xyz = (float4) (x, y, z);
}
