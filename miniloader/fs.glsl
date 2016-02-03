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

float	iterControl(vec2 z, vec2 c)
{
	float	a = 0;

	while (a < param.y)
	{
		z = eq1(z, c);
		if ( (z.x * z.x + z.y * z.y) >= param.x )
			break;
		a++;
	}
	return (a / param.y);
}

float	lineDist(vec2 p, vec3 l)
{
	float		d;

	d = l.x * p.x + l.y * p.y + l.z;
	d = abs(d) / (sqrt(l.x*l.x + l.y*l.y));
	return d;
}

float	iterDist(vec2 z, vec2 c)
{
	float a = 0;
	float dist = 1e20f;
	vec2 point = vec2(0.285, 0.01);
	vec3 line = vec3(0.285, 0.01, 1.15);

	while (a < param.y)
	{
		z = eq1(z, c);
		if ( (z.x * z.x + z.y * z.y) >= param.x )
			break;
		a++;
		dist = min(dist, length(z - point));
		dist = min(dist, lineDist(z, line));
	}
	return (sqrt(dist));
}

void main()
{
	vec2 z = gl_FragCoord.xy / res;
//	z *= res/min(res.x,res.y);

	z.x = grid.x + ( grid.y - grid.x ) * z.x;
	z.y = grid.z + ( grid.w - grid.z ) * z.y;

//	z = vec2(0.0f, 0.0f);
//	vec2 c = z;
	vec2 c = vec2(mousePos);
	c.x = grid.x + ( grid.y - grid.x ) * c.x;
	c.y = grid.z + ( grid.w - grid.z ) * c.y;

//	float col = iterControl(z, c);
	float col = iterDist(z, c);
		
	vec3 color = vec3(1.0f - col, 0, col);
	finalColor = vec4(color, 1.0);
}
