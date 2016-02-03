#version 410 core
#define M_PI 3.1415926535897932384626433832795

uniform vec2 mousePos;
uniform vec2 res;

out vec4 finalColor;

float	spInter(vec3 origin, vec3 dir, vec3 spCenter, float spRadius)
{
	float d;
	vec3 oc = origin - spCenter;
	float noc = length(oc);
	float Xoc = dot(dir, oc);

	float delta = Xoc*Xoc - noc*noc + spRadius*spRadius;
	if (delta < 0)
		return (-1);
	if (delta < 0.001)
		return (-Xoc);

	float d1 = - Xoc - sqrt(delta);
	float d2 = - Xoc + sqrt(delta);

	if (d1 > d2)
		return d2;
	return d1;
}

float	plInter(vec3 origin, vec3 dir, vec3 plPoint, vec3 plN, out vec3 op)
{
	float d = -1;
	float a = dot((plPoint - origin), plN);
	float b = dot(dir, plN);
	
	if (b < - 0.0001 || b > 0.0001)
		d = a / b;
	op = d * dir + origin;
	return d;
}

void main()
{
	vec3	eye = vec3(0., 0., 0);
	vec3	up	= vec3(0., 1., 0.);
	vec3	look = vec3(0.0, 0.0, 0.0);
	vec3	sun = vec3(3, 3, -2);
	float	fov = 90 * M_PI / 180;
	float	eps = 0.0001;

	vec3 sr = vec3(0.0, 0.0, -5);
	float r = 5;

	vec3 plP = vec3(0, -1, 0);
	vec3 plN = vec3(0, 1, 0);

	vec2 screenSpace = (2.0 * (gl_FragCoord.xy / res.xy) - 1.0);
	vec3 cameraSpace;
	cameraSpace.x = screenSpace.x * (res.x/res.y) * tan(fov/2);
	cameraSpace.y = screenSpace.y * tan(fov/2);
	cameraSpace.z = -1;

	vec3 dir = normalize(cameraSpace - eye);

//	float dist = spInter(eye, dir, sr, r);
	vec3 op;
	float dist = plInter(eye, dir, plP, plN, op);
	if (dist > 0)
	{
//		float col = length(sun - op);
		float col = sqrt(dist);
		finalColor = vec4(1 - dist, dist, 0., 1.);
	}
	else
	{
		finalColor = vec4(0., 0., .1, 1.);
	}

	// camera matrix
//	vec3 ww = normalize( look - eye );
//	vec3 uu = normalize( cross(ww, up) );
//	vec3 vv = normalize( cross(uu, ww) );
//	vec3 rd = normalize( pos.x*uu + pos.y*vv + 2.0*ww );
	
//	float dist = spInter(eye, rd, look, 3.);
//	if (dist > 0)
//	{
//		finalColor = vec4(0., 0., 0., 0.);
//	}
//	finalColor = vec4(0., 0., .1, 1.);
}
