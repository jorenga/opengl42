#ifndef CALLBACK_H
# define CALLBACK_H

# include <stdio.h>
# include "glInclude.h"

typedef struct		s_uptr
{
	GLfloat*		mousePos;
}					t_uptr;

void            error_callback(int error, const char* description);
void            framebuffer_size_callback(GLFWwindow* window, int w, int h);
void            key_callback(GLFWwindow* window, int key, int scancode,
                                int action, int mods);
void			cursor_position_callback(GLFWwindow* window,
								double xPos, double yPos);


#endif
