#include "callback.h"

void            framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	(void)window;
	glViewport(0, 0, w, h);
}

void            key_callback(GLFWwindow* window, int key, int scancode,
		int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void            error_callback(int error, const char* description)
{
	printf("Error #%d: %s\n", error, description);
}

void			cursor_position_callback(GLFWwindow* window,
		double xPos, double yPos)
{
	t_uptr              *ptr;

	ptr = (t_uptr*)glfwGetWindowUserPointer(window);
	ptr->mousePos[0] = xPos / 1920;
	ptr->mousePos[1] = yPos/ 1050;
}
