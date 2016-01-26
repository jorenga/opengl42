#include "scop.h"

int						winShouldClose(t_glData* data)
{
	return (glfwWindowShouldClose(data->win));
}

void					swap(t_glData* data)
{
	glfwSwapBuffers(data->win);
}

void					run(t_glData* data)
{

	while (!winShouldClose(data))
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		swap(data);
		glfwPollEvents();
	}
}

void					setupParam(t_winInfo* info, char* name, GLfloat width, GLfloat height)
{
	info->winName = name;
	info->width = width;
	info->height = height;
}

int						main()
{
	t_glData			data;
	t_winInfo			info;

	setupParam(&info, "test", 640, 640);
	initOpenGl(&data, &info);

	run(&data);

	cleanOpenGl(&data);
	return (0);
}
