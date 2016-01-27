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



void                    run(GLFWwindow* win, t_shaders *prog)
{
	glUseProgram(prog->prog);
	printf("using program: %u\n", prog->prog);
    while (!glfwWindowShouldClose(win))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    	glfwSwapBuffers(win);
        glfwPollEvents();
    }
	glUseProgram(0);
}


int					main()
{
	GLFWwindow		*win;
	t_shaders		prog;
	GLuint			vao;
	GLuint			vbo;

	win = setOpenGL(1024, 1024, "biatch");
	createShaderProgram(&prog, "vs.glsl", "fs.glsl");

	printf("prog value: vs_id: %u - fs_id: %u - prog_id: %u\n", prog.vs, prog.fs, prog.prog);

	if (!win)
		return (0);

//	VBO SETUP
	glGenBuffers(1, &vbo);

//	GLfloat points[] = {
//		-0.75f, -0.75f,
//		0.75f, -0.75f,
//		-0.75f,  0.75f,
//		0.75f,  0.75f,
//	};
	GLfloat points[] = {
		-1.f, -1.f,
		 1.f, -1.f,
		-1.f,  1.f,
		 1.f,  1.f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	// Specify layout of point data
	GLint posAttrib = glGetAttribLocation(prog.prog, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

//	VBO SETUP

	run(win, &prog);

	glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
	cleanShaders(prog);
	cleanOpenGL(win);
	return (0);
}
