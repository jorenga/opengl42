__kernel void	initParticles(__global float4 *particles)
{
	const int	i = get_global_id(0);
	float		x, y, z, w;

	if (i  >= MAXGID)
		return ;

	x = i % 10 - 5.0f;
	y = int(i / 100.0f) - 5.0f;
	z = int((i % 100) / 10.0f) - 5.0f;
	w = 1.0f;

	particles[i] = (float4) (x, y, z, w);
}
