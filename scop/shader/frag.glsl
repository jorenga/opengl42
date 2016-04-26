#version 410
#define M_PI 3.141592

uniform float c;
uniform int nbPrim;

in vec4 fragVert;
in vec4	fragColor;

out vec4 finalColor;

uniform sampler2D tex;
uniform sampler2D scale;

void main()
{
	vec4	texCol;
	vec4	priCol;

	texCol = texture(tex, (fragVert.xy + 1 + fragVert.z) / 2);
//	texCol = texture(tex, fragVert.xy);

	float a, b, c;
	a = gl_PrimitiveID;
	b = nbPrim - 1;
	c = a / b;
	priCol = texture(scale, vec2(c, 1));

//	finalColor = texCol * c + priCol * (1 - c);
	finalColor = priCol;
//	finalColor = texCol;
}
