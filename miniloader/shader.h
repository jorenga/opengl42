#ifndef SHADER_H
# define SHADER_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "glInclude.h"

# define BUFLEN			4096

typedef struct			s_shaders
{
	GLuint				prog;
	GLuint				vs;
	GLuint				fs;
}						t_shaders;

GLuint					createShader(GLenum type, char* filename);
GLuint					createProgram(GLuint vs, GLuint fs);
int						createShaderProgram(t_shaders *s, char* VSfile, char* FSfile);
void					cleanShaders(t_shaders s);

#endif
