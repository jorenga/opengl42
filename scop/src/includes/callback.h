#ifndef CALLBACK_H
# define CALLBACK_H

# include <stdio.h>
# include "gl_include.h"
# include "gl_struct.h"

void 			error_callback(int error, const char* description);
void 			key_callback(GLFWwindow* window, int key, int scancode,
								int action, int mods);


#endif
