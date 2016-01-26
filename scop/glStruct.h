#ifndef GLSTRUCT_H
# define GLSTRUCT_H

# include "glInclude.h"

typedef struct			s_glData
{
	GLFWwindow*			win;
}						t_glData;

typedef struct			s_winInfo
{
	char*				winName;
	GLfloat				width;
	GLfloat				height;
}						t_winInfo;

#endif
