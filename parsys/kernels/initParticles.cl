__kernel void	initParticles(__global float4 *particles)
{
	const int	i = get_global_id(0);
	float		x, y, z, w;

	if (i  >= MAXGID)
		return ;

	x = i % int(PPERLINE) - (PPERLINE / 2);
	y = int(i / int(PPERLINE * PPERLINE)) - (PPERLINE / 2);
	z = int((i % int(PPERLINE * PPERLINE)) / PPERLINE) - (PPERLINE / 2);
	w = 1.0f;

	particles[i] = (float4) (x, y, z, w);
}
