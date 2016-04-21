#include "callback.h"

static void				check_press(t_user_ptr *ptr, int key)
{
	float				step;

	step = 0.2;
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

static void				check_release(t_user_ptr *ptr, int key)
{
	float				step;

	step = 0.2;
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

void					key_callback(GLFWwindow* window, int key, int scancode,
								int action, int mods)
{
	t_user_ptr			*ptr;

	ptr = (t_user_ptr*)(glfwGetWindowUserPointer(window));
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (action == GLFW_PRESS)
	{
		check_press(ptr, key);
	}
	if (action == GLFW_RELEASE)
	{
		check_release(ptr, key);
	}
	(void)scancode;
	(void)mods;
}

void			error_callback(int error, const char* description)
{
	printf("Error #%d: %s\n", error, description);
}
