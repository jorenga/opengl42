#version 410

uniform mat4 P;
uniform mat4 R;
uniform vec4 T;

in vec4 in_Position;

out vec4 pColor;

void main()
{
	in_color = vec4(1.0, 1.0, 1.0, 1.0);
	gl_PointSize = 2.0;
	gl_Position = P * M * in_Position;
}
