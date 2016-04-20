#ifndef GL_CONTEXT_H
# define GL_CONTEXT_H

# include "gl_include.h"
# include "gl_struct.h"
# include "callback.h"

int						init_openGL(t_gl_data* data, t_win_info* win_info);
void					clean_openGL(t_gl_data* data);
void					set_hint();
void					set_callback(GLFWwindow* win);

#endif
