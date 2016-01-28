#include "miniloader.h"
#include <sys/time.h>

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
    glfwSetCursorPosCallback(win, cursor_position_callback);
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

void                printT(unsigned long int t)
{
    int             m, s, ms, us;

    m = (t / 60000000);
    s = (t / 1000000) % 60;
    ms = (t / 1000) % 1000;
    us = t % 1000;
//    fprintf(stderr, "Parsing time: %dm%ds%dms%dus\n", m, s, ms, us);
	fprintf(stderr, "%u\n", 1000000 / (ms + us) );
}

void				addParamToProgram(GLFWwindow *win, t_shaders *prog)
{
	GLint			uloc_MousePos;
	t_uptr			*ptr;

	uloc_MousePos = glGetUniformLocation(prog->prog, "mousePos");

	ptr = (t_uptr*)glfwGetWindowUserPointer(win);
	glUniform2fv(uloc_MousePos, 1, ptr->mousePos);
}

void                    run(GLFWwindow* win, t_shaders *prog)
{
//	struct timeval		start, end;
//	unsigned long int	s, e;

	glUseProgram(prog->prog);
	printf("using program: %u\n", prog->prog);
    while (!glfwWindowShouldClose(win))
    {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	gettimeofday(&start, NULL);
		addParamToProgram(win, prog);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//	gettimeofday(&end, NULL);

    	glfwSwapBuffers(win);
        glfwPollEvents();

//		s = start.tv_sec * 1000000 + start.tv_usec;
//		e = end.tv_sec * 1000000 + end.tv_usec;
//		printT(e - s);
    }
	glUseProgram(0);
}

void				createVertexObject(t_vertexObject *vo, t_shaders *s)
{
	glGenBuffers(1, &(vo->vbo));

	GLfloat points[] = {
		-1.f, -1.f,
		 1.f, -1.f,
		-1.f,  1.f,
		 1.f,  1.f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, vo->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	glGenVertexArrays(1, &(vo->vao));
	glBindVertexArray(vo->vao);
	
	GLint posAttrib = glGetAttribLocation(s->prog, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void					cleanVertexObject(t_vertexObject vo)
{
	glDeleteBuffers(1, &(vo.vbo));
    glDeleteVertexArrays(1, &(vo.vao));
}

void					setShaderParam(t_shaders *prog, GLfloat w, GLfloat h)
{
	GLint			uloc_res;
	GLfloat			*nres;

	glUseProgram(prog->prog);
	nres = (GLfloat*)malloc(sizeof(GLfloat) * 2);
	nres[0] = w;
	nres[1] = h;
	uloc_res = glGetUniformLocation(prog->prog, "res");

	printf("nres: %f  %f\n", nres[0], nres[1]);
	glUniform2fv(uloc_res, 1, nres);
	glUseProgram(0);
}

int						main()
{
	GLFWwindow			*win;
	t_shaders			prog;
	t_vertexObject		vo;
	t_uptr				*userPtr;

	win = setOpenGL(WIDTH, HEIGHT, "biatch");
	if (!win)
		return (0);

	createShaderProgram(&prog, "vs.glsl", "fs.glsl");
	setShaderParam(&prog, WIDTH, HEIGHT);

	createVertexObject(&vo, &prog);

	userPtr = (t_uptr*)malloc(sizeof(t_uptr));
	userPtr->mousePos = (GLfloat*)malloc(sizeof(GLfloat) * 2);
	glfwSetWindowUserPointer(win, (void *)userPtr);

	run(win, &prog);

	cleanVertexObject(vo);
	cleanShaders(prog);
	cleanOpenGL(win);
	return (0);
}
