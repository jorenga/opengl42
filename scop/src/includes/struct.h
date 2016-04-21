#ifndef STRUCT_H
# define STRUCT_H

# include "gl_include.h"

typedef struct		s_min_max
{
	GLfloat			min_x;
	GLfloat			max_x;
	GLfloat			min_y;
	GLfloat			max_y;
	GLfloat			min_z;
	GLfloat			max_z;
}					t_min_max;

typedef struct		s_vec3
{
	float			x;
	float			y;
	float			z;
}					t_vec3;

typedef struct		s_vec4
{
	GLfloat			x;
	GLfloat			y;
	GLfloat			z;
	GLfloat			w;
}					t_vec4;

typedef struct		s_mesh
{
	t_vec4			*vertices;
	int				vert_pos;
	GLuint			*indices;
	int				ind_pos;
	GLuint			vao;
	GLuint			vbo[2];
	t_min_max		mm;
	t_vec3			center;
	t_vec3			pos;
}					t_mesh;

typedef struct		s_sizes
{
	int				vert_size;
	int				ind_size;
}					t_sizes;

typedef struct		s_tex
{
	GLuint			id;
	GLfloat			*col;
}					t_tex;

typedef struct		s_gl_obj
{
	t_mesh			*mesh;
	GLuint			prog;
	t_tex			tex;
}					t_gl_obj;

#endif
