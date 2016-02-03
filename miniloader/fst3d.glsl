#version 410 core
#define M_PI 3.1415926535897932384626433832795

uniform vec2 mousePos;
uniform vec2 res;

// minX, maxX, minY, maxY
const vec4 grid = vec4(-2.4, 2.4, -1.5, 1.5);
// borne, nbIt
const vec2 param = vec2(8.0, 50.0);

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

vec3	eq(vec3 z, vec3 c)
{
	vec3 nz;

	nz.x = z.x*z.x - z.y*z.y - z.z*z.z + c.x;
	nz.y = 2 * z.x * z.y + c.y;
	nz.z = 2 * z.x * z.z + c.z;
	return nz;
}

vec4	eqQ(vec4 z, vec4 c)
{
	vec4 nz;

	nz.x = z.x*z.x - z.y*z.y - z.z*z.z - z.w*z.w + c.x;
	nz.y = z.x*z.y + z.y*z.x + z.z*z.w - z.w*z.z + c.y;
	nz.z = z.x*z.z + z.z*z.x + z.w*z.y - z.y*z.w + c.z;
	nz.w = z.x*z.w + z.w*z.x + z.y*z.z - z.z*z.y + c.w;
	return (nz);
}

bool        iterateQ(vec4 z, vec4 c)
{
    float a = 0;
    while (a < param.y)
    {
        z = eqQ(z, c);
        if ( (z.x*z.x + z.y*z.y + z.z*z.z + z.w*z.w) >= param.x )
            return true;
        a++;
    }
    return false;
}

bool		castRayQ(vec3 eye, vec3 rd, vec4 c)
{
	float delt = 0.01f;
    float mint = 0.001f;
    float maxt = 10.0f;
    for( float t = mint; t < maxt; t += delt )
    {
        vec3 p = eye + rd*t;
		vec4 po = vec4(p, 0.0);
        if ( iterateQ(po, c) )
        {
            return true;
        }
    }
    return false;
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

bool		iterate(vec3 z, vec3 c)
{
	float a = 0;
	while (a < param.y)
	{
		z = eq(z, c);
		if ( (z.x*z.x + z.y*z.y + z.z*z.z) >= param.x )
			return true;
		a++;
	}
	return false;
}

bool		castRay(vec3 eye, vec3 rd, vec3 c)
{
	float delt = 0.01f;
    float mint = 0.001f;
    float maxt = 10.0f;
    for( float t = mint; t < maxt; t += delt )
    {
        vec3 p = eye + rd*t;
        if ( iterate(p, c) )
        {
            return true;
        }
    }
    return false;
}

void main()
{
	vec3	eye = vec3(1.65826,-1.22975,0.277736);
	vec3	up	= vec3(0., 1., 0.);
	float	eps = 0.0001;

	vec2 pos = 2.0 * ( gl_FragCoord.xy / res.xy ) - 1.0; // bound screen coords to [0, 1]
	vec3 cLook = vec3(eye.x + 1.0, eye.y, 0.0); // lookAt
	// camera matrix
	vec3 ww = normalize( cLook - eye );
	vec3 uu = normalize( cross(ww, up) );
	vec3 vv = normalize( cross(uu, ww) );
	vec3 rd = normalize( pos.x*uu + pos.y*vv + 2.0*ww );
	

//	vec3 c = vec3(mousePos, 0.0);
//	c.x = grid.x + ( grid.y - grid.x ) * c.x;
//	c.y = grid.z + ( grid.w - grid.z ) * c.y;


	vec4 c = vec4(-1.0, 0.2, 0, 0);
//	vec3 c = vec3(0.285, 001., 0.);	

	bool ret = castRayQ(eye, rd, c);
	if (ret)
		finalColor = vec4(1., 0., 0., 1.);
	else
		finalColor = vec4(0., 0., 1., 1.);

//	float a;
//	float step = 0.01f;
//	while (z.z < 2.0f)
//	{
//		a = iterControl(z, c);
//		a = iterDist(c, z);
//		if (a <= eps)
//			break;
//		z.z += step;
//	}
//	float col = a;	

//	vec3 color = vec3(1 - col, 0, col);
//	finalColor = vec4(color, 1.0);
}
