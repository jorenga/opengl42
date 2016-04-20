#include "scop.h"

int						win_should_close(t_gl_data* data)
{
	return (glfwWindowShouldClose(data->win));
}

void					swap(t_gl_data* data)
{
	glfwSwapBuffers(data->win);
}

void					setup_param(t_win_info* info, char* name, GLfloat width, GLfloat height)
{
	info->name = name;
	info->width = width;
	info->height = height;
}

void					setup_clip(t_clip_info* clip, GLfloat aspect)
{
	clip->fov = 45;
	clip->aspect = aspect;
	clip->z_near = 0.1;
	clip->z_far = 1000;
}

void					add_matrices(GLuint prog, float *m, float *p, float c)
{
	GLint				uloc_M;
	GLint				uloc_P;
	GLint				uloc_C;

	uloc_M = glGetUniformLocation(prog, "M");
	uloc_P = glGetUniformLocation(prog, "P");
	uloc_C = glGetUniformLocation(prog, "c");

	glUniformMatrix4fv(uloc_M, 1, GL_FALSE, m);
	glUniformMatrix4fv(uloc_P, 1, GL_FALSE, p);
	glUniform1f(uloc_C, c);
}

void					draw_mesh(t_mesh *mesh)
{
	glDrawElements(GL_TRIANGLES, mesh->ind_pos, GL_UNSIGNED_INT, 0);
}

void					move_mesh(t_gl_data *data, t_mesh *mesh, float *m)
{
	mesh->pos.x += data->input.x;
	mesh->pos.y += data->input.y;
	mesh->pos.z += data->input.z;

	translate_matx(m, mesh->pos.x, mesh->pos.y, mesh->pos.z);
}

void					run(t_gl_data* data, t_mesh *mesh, GLuint prog, float *p)
{
	float				m[16];
	float				al = 0;
	t_user_ptr			up;

	up.input = &(data->input);
	glfwSetWindowUserPointer(data->win, (void*)(&up));

	get_identity_matx(m);
	glUseProgram(prog);
	glBindVertexArray(mesh->vao);
	while (!win_should_close(data))
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	get_identity_matx(m);
	move_mesh(data, mesh, m);
//	translate_matx(m, data->input.x, data->input.y, data->input.z);
		rot_y_matx(m, al);
	translate_matx(m, mesh->center.x * -1 , mesh->center.y * -1 , mesh->center.z * -1);

		add_matrices(prog, m, p, data->input.anim);
		draw_mesh(mesh);

		swap(data);
		glfwPollEvents();
		al += 0.01;
		if (data->input.col == 1 && data->input.anim < 1)
			data->input.anim += 0.01;
		if (data->input.col == -1 && data->input.anim > 0)
			data->input.anim -= 0.01;
		if (data->input.anim > 1)
			data->input.anim = 1;
		if (data->input.anim < 0)
			data->input.anim = 0;
	}
	glBindVertexArray(0);
	glUseProgram(0);
}

void					setup_mesh(t_mesh *mesh, GLuint program)
{
	GLuint				attrloc;

	glGenVertexArrays(1, &(mesh->vao));
	glBindVertexArray(mesh->vao);
	glGenBuffers(2, mesh->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4) * mesh->vert_pos, &(mesh->vertices[0]), GL_STATIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 32, &(cube_vertices[0]), GL_STATIC_DRAW);
	attrloc = glGetAttribLocation(program, "in_Position");
	glVertexAttribPointer(attrloc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->ind_pos, &(mesh->indices[0]), GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 36, &(cube_elements[0]), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void					setup_texture(t_tex *tex, GLuint program)
{
	float				*pixels;
	int					w;
	int					h;

	glGenTextures(1, &(tex->id));
	glBindTexture(GL_TEXTURE_2D, tex->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	pixels = import_bmp_file("chaton.bmp", &w, &h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, pixels);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glUniform1i(glGetUniformLocation(program, "tex"), 0);
}

int						error(char *err)
{
	printf("%s\n", err);
	return (1);
}

void					init_input(t_gl_data *data)
{
	data->input.x = 0;
	data->input.y = 0;
	data->input.z = 0;
	data->input.col = 1;
	data->input.anim = 1;
}

int						main(int ac, char **av)
{
	t_gl_data			data;
	t_win_info			info;
	t_clip_info			clip;

	t_mesh				*mesh;
	GLuint				prog;
	t_tex				tex;

	float				p[16];

	if (ac != 2)
		return (error("please provide file"));
	setup_param(&info, "test", 640, 480);
	setup_clip(&clip, info.width / info.height);
	printf("clip %f\t%f\t%f\t%f\n", clip.fov, clip.aspect, clip.z_near, clip.z_far);
	init_openGL(&data, &info);
	
	init_input(&data);
/*
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
*/
	mesh = parse_obj(av[1]);
	if (!mesh)
		return (error("mesh import failed"));
	else
		error("mesh created");
	prog = get_shader_prog("shader/vert.glsl", "shader/frag.glsl");
	if (!prog)
		return (error("prog creation failed"));

	setup_mesh(mesh, prog);
	setup_texture(&tex, prog);

	get_proj_matx(p, &clip);
	run(&data, mesh, prog, p);

	clean_openGL(&data);
	return (0);
}
