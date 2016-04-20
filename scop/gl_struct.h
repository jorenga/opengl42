#ifndef GL_STRUCT_H
# define GL_STRUCT_H

# include "gl_include.h"

typedef struct			s_input
{
	float				x;
	float				y;
	float				z;
	char				col;
	float				anim;
}						t_input;

typedef struct			s_gl_data
{
	GLFWwindow*			win;
	t_input				input;
}						t_gl_data;

typedef struct			s_win_info
{
	char*				name;
	GLfloat				width;
	GLfloat				height;
}						t_win_info;

typedef struct			s_clip_info
{
	GLfloat				fov;
	GLfloat				aspect;
	GLfloat				z_near;
	GLfloat				z_far;
}						t_clip_info;

typedef struct			s_user_ptr
{
	t_input				*input;
}						t_user_ptr;

#endif
