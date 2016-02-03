#version 410 core
#define M_PI 3.1415926535897932384626433832795

uniform vec2 mousePos;
uniform vec2 res;

// minX, maxX, minY, maxY
const vec4 grid = vec4(-2.4, 2.4, -1.5, 1.5);
// borne, nbIt
const vec2 param = vec2(100.0, 500.0);

out vec4 finalColor;

vec3	eq3D(vec3 z, vec3 c, float n)
{
	float r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	float theta = atan(sqrt(z.x*z.x + z.y*z.y), z.z);
	float phi = atan(z.y,z.x);

	vec3 nz;
	nz.x = pow(r, n) * sin(theta*n) * cos(phi*n);
	nz.y = pow(r, n) * sin(theta*n) * sin(phi*n);
	nz.z = pow(r, n) * cos(theta*n);
	nz = nz + c;
	return nz;
}

float	iterControl(vec3 z, vec3 c)
{
	float a = 0;
	while (a < param.y)
	{
		z = eq3D(z, c, 8);
		if ( (z.x * z.x + z.y * z.y + z.z * z.z) >= param.x ) {
			break;
		}
		a++;
	}
	return (a);	
}

float	iterDist(vec3 z, vec3 c)
{
	float a = 0;
	float dist = 1e20f;
	vec3 point = vec3(0.285, 0.01, 0.0f);

	while (a < param.y)
	{
		z = eq3D(z, c, 8);
		if ( (z.x*z.x + z.y*z.y + z.z*z.z) >= param.x )
			break;
		a++;
		dist = min(dist, length(z - point));
	}
	return (sqrt(dist));
}

void main()
{
	float	eps = 0.0001;
	vec3 z = vec3(gl_FragCoord.xy / res, -2.0);
//	z *= res/min(res.x,res.y);

	z.x = grid.x + ( grid.y - grid.x ) * z.x;
	z.y = grid.z + ( grid.w - grid.z ) * z.y;

//	vec3 c = z;
	vec3 c = vec3(mousePos, 0.0);
	c.x = grid.x + ( grid.y - grid.x ) * c.x;
	c.y = grid.z + ( grid.w - grid.z ) * c.y;

	float a;
	float step = 0.01f;
	while (z.z < 2.0f)
	{
//		a = iterControl(z, c);
		a = iterDist(c, z);
		if (a <= eps)
			break;
		z.z += step;
	}
	float col = a;	

	vec3 color = vec3(1 - col, 0, col);
	finalColor = vec4(color, 1.0);
}
