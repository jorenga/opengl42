#include "miniloader.h"

void                    setHint()
{
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void                    setCallback(GLFWwindow* win)
{
	glfwSetErrorCallback(error_callback);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
	glfwSetKeyCallback(win, key_callback);
}

GLFWwindow*				setOpenGL(float width, float height, char* name)
{
	GLFWwindow		*win;

	if (!glfwInit())
		return (NULL);
	setHint();
	win = glfwCreateWindow(width, height, name, NULL, NULL);
	if (! win )
	{
		glfwTerminate();
		return (NULL);
	}
	setCallback(win);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, (int)width, (int)height);
	return (win);
}

void                    cleanOpenGL(GLFWwindow* win)
{
	glfwDestroyWindow(win);
	glfwTerminate();
}



void                    run(GLFWwindow* win, t_shaders prog)
{

    while (!glfwWindowShouldClose(win))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(prog.prog);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glUseProgram(0);

    	glfwSwapBuffers(win);
        glfwPollEvents();
    }
}


int					main()
{
	GLFWwindow		*win;
	t_shaders		prog;

	win = setOpenGL(1024, 1024, "biatch");
	createShaderProgram(&prog, "vs.glsl", "fs.glsl");
	if (!win)
		return (0);

	run(win, prog);

	cleanShaders(prog);
	cleanOpenGL(win);
	return (0);
}
