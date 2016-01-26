#ifndef GLCONTEXT_H
# define GLCONTEXT_H

# include "glInclude.h"
# include "glStruct.h"
# include "callback.h"

int						initOpenGl(t_glData* data, t_winInfo* winInfo);
void					cleanOpenGl(t_glData* data);
void					setHint();
void					setCallback(GLFWwindow* win);

#endif
