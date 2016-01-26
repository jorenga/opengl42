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
