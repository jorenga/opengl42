#version 410
#define M_PI 3.14159

uniform float c;

in vec4 fragVert;
in vec4	fragColor;

out vec4 finalColor;

uniform sampler2D tex;

void main()
{
	vec4	texCol;
	vec4	priCol;


//	vec2	t = fragVert.xy;
//	t.x /= 4 * cos(t.x) * M_PI;
//	t.y /= 4 * cos(t.y) * M_PI;
	texCol = texture(tex, (fragVert.xy + 1 + fragVert.z) / 2);
//	texCol = texture(tex, (t + 1 + fragVert.z) /2);


//	priCol = 1 -texCol;
	priCol = vec4(0.01f, 0.01f, 0.01f, 1.0f) * (gl_PrimitiveID % 100);

	finalColor = texCol * c + priCol * (1 - c);
}
