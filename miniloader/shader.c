#include "shader.h"

GLuint					createShaderProgram(char* VSfile, char* FSfile)
{
	GLuint				vs, fs;
	GLuint				prog;

	vs = createShader(GL_VERTEX_SHADER, VSfile);
	fs = createShader(GL_FRAGMENT_SHADER, FSfile);
	prog = createProgram(vs, fs);
	return (prog);
}

char*					fileToBuf(char* filename)
{
	char				buf[2048];
	char*				outfile;


}

GLuint					createShader(GLenum type, char* filename)
{

}
