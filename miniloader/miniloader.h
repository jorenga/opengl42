#ifndef SCOP_H
# define SCOP_H

# include <unistd.h>
# include "glInclude.h"
# include "callback.h"
# include "shader.h"

# define WIDTH			1280
# define HEIGHT			720

typedef struct			s_vertexObject
{
	GLuint				vao;
	GLuint				vbo;
}						t_vertexObject;

#endif
