#version 410

uniform mat4 P;
uniform mat4 M;

in vec4 in_Position;

out vec4 fragVert;
out vec4 fragColor;

void		main()
{
	fragColor = vec4(0.7, 0.0, 1.0, 1.0);
	fragVert = in_Position;
	gl_Position = P * M * in_Position;
}
