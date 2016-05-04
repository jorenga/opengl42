#include "scop.h"

void				add_matrices(GLuint prog, float *m, float *p, t_input *i)
{
	GLint			uloc_m;
	GLint			uloc_p;
	GLint			uloc_anim;
	GLint			uloc_tex;
	GLint			uloc_map;

	printf("p:");
	int a = 0;
	while (a < 16)
	{
		for (int j = 0; j < 4 ; j++)
		{
			printf("%f ", p[a]);
			a++;
		}
		printf("\n");
	}
	uloc_m = glGetUniformLocation(prog, "M");
	uloc_p = glGetUniformLocation(prog, "P");
	uloc_anim = glGetUniformLocation(prog, "c");
	uloc_tex = glGetUniformLocation(prog, "texUnit");
	uloc_map = glGetUniformLocation(prog, "map");
	glUniformMatrix4fv(uloc_m, 1, GL_FALSE, m);
	glUniformMatrix4fv(uloc_p, 1, GL_FALSE, p);
	glUniform1f(uloc_anim, i->anim);
	glUniform1i(uloc_tex, i->tex);
	glUniform1i(uloc_map, i->mapping);
}

void				run(t_gl_data* data, t_mesh *mesh, GLuint prog, float *p)
{
	float			m[16];
	float			al = 0;
	t_user_ptr		up;

	up.input = &(data->input);
	glfwSetWindowUserPointer(data->win, (void*)(&up));
	glBindVertexArray(mesh->vao);
	while (!(glfwWindowShouldClose(data->win)))
	{
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		move_mesh(data, mesh, m, &al);
		add_matrices(prog, m, p, &(data->input));
		glDrawElements(GL_TRIANGLES, mesh->ind_pos, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(data->win);
		glfwPollEvents();
	}
	glBindVertexArray(0);
	glUseProgram(0);
}

void				setup_mesh(t_mesh *mesh, GLuint program)
{
	GLuint			attrloc;

	glGenVertexArrays(1, &(mesh->vao));
	glBindVertexArray(mesh->vao);
	glGenBuffers(2, mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4) * mesh->vert_pos,
			&(mesh->vertices[0]), GL_STATIC_DRAW);
	attrloc = glGetAttribLocation(program, "in_Position");
	glVertexAttribPointer(attrloc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->ind_pos,
			&(mesh->indices[0]), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void				setup_texture(t_tex *tex, GLuint program, t_mesh *mesh)
{
	float			*texels;
	int				w;
	int				h;

	glGenTextures(2, tex->id);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->id[0]);
	texels = import_bmp_file("textures/chaton.bmp", &w, &h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, texels);
	glUniform1i(glGetUniformLocation(program, "tex0"), 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(texels);
	
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, tex->id[1]);
	texels = import_bmp_file("textures/weird1.bmp", &w, &h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, texels);
	glUniform1i(glGetUniformLocation(program, "tex1"), 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(texels);

	glActiveTexture(GL_TEXTURE0 + 2);
	glBindTexture(GL_TEXTURE_2D, tex->id[2]);
	texels = import_bmp_file("textures/wood1.bmp", &w, &h);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, texels);
	glUniform1i(glGetUniformLocation(program, "tex2"), 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(texels);

	glUniform1i(glGetUniformLocation(program, "nbPrim"), mesh->nb_prim);
}

int					main(int ac, char **av)
{
	t_gl_data		data;
	t_gl_obj		gl;
	float			p[16];

	if (ac != 2)
		return (error("please provide obj file"));
	setup_param(&(data.win_info), "test", 640, 480);
	setup_clip(&(data.clip_info), data.win_info.width / data.win_info.height);
	init_openGL(&data, &(data.win_info));
	init_input(&data);
	gl.mesh = parse_obj(av[1]);
	if (!(gl.mesh))
		return (error("mesh import failed"));
	gl.prog = get_shader_prog("shader/vert.glsl", "shader/frag.glsl");
	if (!gl.prog)
		return (error("prog creation failed"));
	glUseProgram(gl.prog);
	setup_mesh(gl.mesh, gl.prog);
	setup_texture(&(gl.tex), gl.prog, gl.mesh);
	get_proj_matx(p, &(data.clip_info));
	run(&data, gl.mesh, gl.prog, p);
	clean_openGL(&data);
	return (0);
}
