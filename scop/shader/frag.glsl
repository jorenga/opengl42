#version 410
#define M_PI 3.141592

uniform float c;
uniform int	texUnit;
uniform int	map;
uniform int nbPrim;

in vec4 fragVert;
in vec4	fragColor;

out vec4 finalColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
	vec2	texCoord;
	vec4	texCol;
	vec4	priCol;

	clamp(c, 0, 1);
	if (map == 0)
		texCoord = (fragVert.xy + 1 + fragVert.z) / 2;
	else if (map > 0)
		texCoord = fragVert.zy;
	if (texUnit == 0)
		texCol = texture(tex0, texCoord);
	else if (texUnit == 1)
		texCol = texture(tex1, texCoord);
	else if (texUnit == 2)
		texCol = texture(tex2, texCoord);

	float d = gl_PrimitiveID / (nbPrim - 1.0);
	priCol = vec4(d);

	finalColor = mix(texCol, priCol, c);
}
