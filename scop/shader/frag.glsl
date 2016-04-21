#version 410
#define M_PI 3.141592

uniform float c;

in vec4 fragVert;
in vec4	fragColor;

out vec4 finalColor;

uniform sampler2D tex;

void main()
{
	vec4	texCol;
	vec4	priCol;
//	float	r = 2.0f;
//	vec2	t;

//	r = fragVert.z;
//	t.x = acos(fragVert.z / r) / M_PI;
//	t.y = acos(fragVert.x / r * sin(M_PI * t.x)) / (2 * M_PI);

//	texCol = texture(tex, t);
	texCol = texture(tex, (fragVert.xy + 1 + fragVert.z) / 2);

	priCol = vec4(0.01f, 0.01f, 0.01f, 1.0f) * (gl_PrimitiveID % 100);

	finalColor = texCol * c + priCol * (1 - c);
}
