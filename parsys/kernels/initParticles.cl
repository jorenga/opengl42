__kernel void	initParticles(__global float4 *particles, __global float4 *particlesV)
{
	const int	i = get_global_id(0);
	float		x, y, z, w;

	if (i  >= MAXGID)
		return ;

	x = i % int(PPERLINE) - (PPERLINE / 2);
	z = int(i / int(PPERLINE * PPERLINE)) - (PPERLINE / 2);
	y = int((i % int(PPERLINE * PPERLINE)) / PPERLINE) - (PPERLINE / 2);
	w = 1.0f;

//	particles[i] = (float4) (x, y, z, w);
	particles[i] = (float4) (x * 50.0f, y * 50.0f, z * 50.0f, w);
	particlesV[i] = (float4) (0.0f, 0.0f, 0.0f, 0.0f);
}
