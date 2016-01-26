#include "glContext.h"

void					setHint()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
  	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void					setCallback(GLFWwindow* win)
{
    glfwSetErrorCallback(error_callback);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetKeyCallback(win, key_callback);
//  glfwSetCursorPosCallback(win, cursor_position_callback);
//	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

int						initOpenGl(t_glData* data, t_winInfo* winInfo)
{
    int					width;
	int					height;

    if (!glfwInit())
        return (0);
	setHint();
    data->win = glfwCreateWindow(winInfo->width, winInfo->height,
									winInfo->winName, NULL, NULL);
    if (! data->win )
    {
        glfwTerminate();
        return (0);
    }
	setCallback(data->win);	
    glfwMakeContextCurrent(data->win);
    glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwGetFramebufferSize(data->win, &(width), &(height));
    glViewport(0, 0, width, height);
	return (1);
}

void					cleanOpenGl(t_glData* data)
{
	glfwDestroyWindow(data->win);
	glfwTerminate();
}
