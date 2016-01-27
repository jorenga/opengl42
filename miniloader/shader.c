#include "shader.h"

int						createShaderProgram(t_shaders *s, char* VSfile, char* FSfile)
{
	GLuint				vs, fs;
	GLuint				prog;

	vs = createShader(GL_VERTEX_SHADER, VSfile);
	fs = createShader(GL_FRAGMENT_SHADER, FSfile);
	prog = createProgram(vs, fs);

	s->prog = prog;
	s->vs = vs;
	s->fs = fs;
	return (1);
}

void        			realloc_cat(char** src, char* str, int size)
{
    char*   			s;
    int     			i = 0;
    int     			len = strlen(*src);

    s = (char*)malloc(sizeof(char) * (len + size + 1));
    while (i < len)
    {
        s[i] = (*src)[i];
        i++;
    }
    i =  0;
    while (i < size)
    {
        s[i + len] = str[i];
        i++;
    }
    s[i + len] = '\0';
    free(*src);
    *src = s;
}

char*           		fileToBuf(char* filename)
{
    char       		 buf[BUFLEN];
    int			fd = open(filename, O_RDONLY);
    int         ret;
    char*       src;

    src = (char*)malloc(sizeof(char));
    *src = '\0';
    while ((ret = read(fd, buf, BUFLEN)) != 0)
    {
        realloc_cat(&src, buf, ret);
    }
    return (src);
}

GLuint					createShader(GLenum type, char* filename)
{
	GLuint				shader;
	GLint				shader_ok;
	GLsizei				log_length;
	char				info_log[8192];
	char				*source;

	source = fileToBuf(filename);
	shader = glCreateShader(type);
	if (shader != 0)
	{
		glShaderSource(shader, 1, &source, NULL);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
		if (shader_ok != GL_TRUE)
		{
			fprintf(stderr, "ERROR: Failed to compile %s shader\n", (type == GL_FRAGMENT_SHADER) ? "fragment" : "vertex" );
			glGetShaderInfoLog(shader, 8192, &log_length,info_log);
			fprintf(stderr, "ERROR: \n%s\n\n", info_log);
			glDeleteShader(shader);
			return (0);
		}
	}
	return (shader);
}

GLuint			createProgram(GLuint vs, GLuint fs)
{
	GLuint		program = 0u;
	GLint		program_ok;
	GLsizei		log_length;
	char		info_log[8192];

	program = glCreateProgram();
	if (program != 0u)
	{
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
		if (program_ok != GL_TRUE)
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

void			cleanShaders(t_shaders s)
{
	glDeleteProgram(s.prog);
	glDeleteShader(s.vs);
	glDeleteShader(s.fs);
}
