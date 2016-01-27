#version 410 core
#define M_PI 3.1415926535897932384626433832795

const vec2 res = vec2(1024, 1024);
out vec4 finalColor;

void main()
{
	vec2 p = gl_FragCoord.xy / res;
	p *= res/min(res.x,res.y);
	finalColor = vec4(p, 0.0, 1.0);
}
