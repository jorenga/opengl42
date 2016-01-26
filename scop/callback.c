#include "callback.h"

void 			framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
/*	t_user_ptr				*ptr;

	ptr = reinterpret_cast<t_user_ptr *>(glfwGetWindowUserPointer(window));
	ptr->winInfo->width = w;
	ptr->winInfo->height = h;*/
    glViewport(0, 0, w, h);
}

void			key_callback(GLFWwindow* window, int key, int scancode,
								int action, int mods)
{
/*	t_user_ptr				*ptr;

	ptr = reinterpret_cast<t_user_ptr *>(glfwGetWindowUserPointer(window));*/
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

/*
void			cursor_position_callback(GLFWwindow* window,
								double xPos, double yPos)
{
}
*/

void			error_callback(int error, const char* description)
{
	printf("Error #%d: %s\n", error, description);
}
