#include "shader.h"

char        		*filetobuf(const char *file)
{
	FILE			*fptr;
	long			length;
	char			*buf;

	fptr = fopen(file, "rb");
	if (!fptr)
		return NULL;
	fseek(fptr, 0, SEEK_END);
	length = ftell(fptr);
	buf = (char*)malloc(length + 1);
	fseek(fptr, 0, SEEK_SET);
	fread(buf, length, 1, fptr);
	fclose(fptr);
	buf[length] = 0;
	return buf;
}

GLuint				create_shader(GLenum type, char *filename)
{
	GLuint			shader;
	GLint			ret;
	GLsizei			log_length;
	char			info_log[8192];
	const char		*source;

	source = filetobuf(filename);
	shader = glCreateShader(type);
	if (shader)
	{
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
		if (ret != GL_TRUE)
		{
			fprintf(stderr, "ERROR: Failed to compile %s shader\n",
					(type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex" );
			glGetShaderInfoLog(shader, 8192, &log_length,info_log);
			fprintf(stderr, "ERROR: \n%s\n\n", info_log);
			glDeleteShader(shader);
			return (0);
		}
	}
	return (shader);
}

GLuint				create_program(GLuint vs, GLuint fs)
{
	GLuint			program;
	GLint			ret;
	GLsizei			log_length;
	char			info_log[8192];

	program = glCreateProgram();
	if (program)
	{
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &ret);
		if (ret != GL_TRUE)
		{
			fprintf(stderr, "ERROR, failed to link shader program\n");
			glGetProgramInfoLog(program, 8192, &log_length, info_log);
			fprintf(stderr, "ERROR: \n%s\n\n", info_log);
			glDeleteProgram(program);
			glDeleteShader(vs);
			glDeleteShader(fs);
			return (0);
		}
	}
	return (program);
}

GLuint				get_shader_prog(char *vs_file, char *fs_file)
{
	GLuint			vs;
	GLuint			fs;
	GLuint			prog;

	vs = create_shader(GL_VERTEX_SHADER, vs_file);
	fs = create_shader(GL_FRAGMENT_SHADER, fs_file);
	if (!vs || !fs)
		return (0);
	prog = create_program(vs, fs);
	return (prog);
}
