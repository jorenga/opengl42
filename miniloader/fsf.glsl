#version 410 core
#define M_PI 3.1415926535897932384626433832795

uniform vec2 mousePos;
uniform vec2 res;

// minX, maxX, minY, maxY
const vec4 grid = vec4(-2.4, 2.4, -1.5, 1.5);
// borne, nbIt
const vec2 param = vec2(100.0, 500.0);

out vec4 finalColor;

vec2	eq1(vec2 z, vec2 c)
{
	vec2 nz;

	nz.x = z.x * z.x - z.y * z.y + c.x;
	nz.y = 2 * z.x * z.y + c.y;
	return nz;
}

vec2	eq2(vec2 z, vec2 c)
{
	vec2 nz;

	nz.x = exp(z.x*z.x) / exp(z.y*z.y) * cos(2 * z.x * z.y) + c.x;
	nz.y = exp(z.x*z.x) / exp(z.y*z.y) * sin(2 * z.x * z.y) + c.y;
	return nz;
}

vec2	eq3(vec2 z, vec2 c)
{
	vec2 nz;

	nz.x = exp(z.x) * cos(z.y) + c.x;
	nz.y = exp(z.x) * sin(z.y) + c.y;
	return nz;
}

float	iterControl(vec2 z, vec2 c)
{
	float a = 0;
	while (a < param.y)
	{
		z = eq1(z, c);
		if ( (z.x * z.x + z.y * z.y) >= param.x )
			break;
		a++;
	}
	return (a);	
}

void	main()
{
	vec2 z = gl_FragCoord.xy / res;
//	z *= res/min(res.x,res.y);

	z.x = grid.x + ( grid.y - grid.x ) * z.x;
	z.y = grid.z + ( grid.w - grid.z ) * z.y;

//	vec2 c = vec2(0.285f, 0.01f);
	vec2 c = mousePos;
	c.x = grid.x + ( grid.y - grid.x ) * c.x;
	c.y = grid.z + ( grid.w - grid.z ) * c.y;

//	float a = iterControl(c, z);
	float a = iterControl(z, c);
	float col = a / param.y;	

	vec3 color = vec3(1.0f / a, 0, col);

	finalColor = vec4(color, 1.0);
//	finalColor = vec4(z.x, col, z.y, 1.0);
}
