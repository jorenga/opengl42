#version 410

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 in_Position;

out vec4 pColor;

void main()
{
	pColor = vec4(1.0, 1.0, 1.0, 1.0);
	gl_Position = P * V * M * in_Position;
	gl_PointSize = 1.0;
}
