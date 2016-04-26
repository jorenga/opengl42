#include "obj_import.h"

void				allocate_mesh(t_mesh *mesh, t_sizes *sizes)
{
	mesh->vertices = malloc(sizeof(t_vec4) * sizes->vert_size);
	mesh->indices =  malloc(sizeof(GLuint) * sizes->ind_size);
	mesh->vert_pos = 0;
	mesh->ind_pos = 0;
	mesh->step = 1.0 / sizes->nb_faces;
	mesh->nb_prim = sizes->ind_size / 3;
	mesh->colors = malloc(sizeof(float) * mesh->nb_prim * 3);
	mesh->col_pos = 0;
	mesh->ramp = 0;
	printf("nb faces: %d\tnb_prim: %d\n" , sizes->nb_faces, mesh->nb_prim);
}
void				init_min_max(t_mesh *m)
{
	m->mm.min_x = 10000;
	m->mm.max_x = -10000;
	m->mm.min_y = 10000;
	m->mm.max_y = -10000;
	m->mm.min_z = 10000;
	m->mm.max_z = -10000;
}
