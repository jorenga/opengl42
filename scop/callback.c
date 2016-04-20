#include "callback.h"

void 			framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
/*	t_user_ptr				*ptr;

	ptr = reinterpret_cast<t_user_ptr *>(glfwGetWindowUserPointer(window));
	ptr->winInfo->width = w;
	ptr->winInfo->height = h;*/
    glViewport(0, 0, w, h);
	(void)window;
}

void			key_callback(GLFWwindow* window, int key, int scancode,
								int action, int mods)
{
	t_user_ptr				*ptr;
	float					step;

	step = 0.2;
	ptr = (t_user_ptr*)(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_D)
			ptr->input->x = step;
		if (key == GLFW_KEY_A)
			ptr->input->x = -step;
		if (key == GLFW_KEY_W)
			ptr->input->y = step;
		if (key == GLFW_KEY_S)
			ptr->input->y = -step;
		if (key == GLFW_KEY_R)
			ptr->input->z = step;
		if (key == GLFW_KEY_F)
			ptr->input->z = -step;
		if (key == GLFW_KEY_C)
			ptr->input->col *= -1;
	}
	if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_D)
			ptr->input->x = 0;
		if (key == GLFW_KEY_A)
			ptr->input->x = 0;
		if (key == GLFW_KEY_W)
			ptr->input->y = 0;
		if (key == GLFW_KEY_S)
			ptr->input->y = 0;
		if (key == GLFW_KEY_R)
			ptr->input->z = 0;
		if (key == GLFW_KEY_F)
			ptr->input->z = 0;
	}
	(void)scancode;
	(void)mods;
}

void			error_callback(int error, const char* description)
{
	printf("Error #%d: %s\n", error, description);
}
