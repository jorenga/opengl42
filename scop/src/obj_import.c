# include "obj_import.h"

void				add_vertices(t_mesh *mesh, char *line)
{
	t_vec4			v;

	v.w = 1;
	sscanf(line, "v %e %e %e %e", &(v.x), &(v.y), &(v.z), &(v.w));
	mesh->vertices[mesh->vert_pos] = v;
	mesh->vert_pos++;
	if (v.x > mesh->mm.max_x)
		mesh->mm.max_x = v.x;
	else if (v.x < mesh->mm.min_x)
		mesh->mm.min_x = v.x;
	if (v.y > mesh->mm.max_y)
		mesh->mm.max_y = v.y;
	else if (v.y < mesh->mm.min_y)
		mesh->mm.min_y = v.y;
	if (v.z > mesh->mm.max_z)
		mesh->mm.max_z = v.z;
	else if (v.z < mesh->mm.min_z)
		mesh->mm.min_z = v.z;
}

void				add_face(t_mesh *mesh, char *line)
{
	char			*s;
	char			**array;
	int				len;
	int				i;

	i = 0;
	s = get_faces(line);
	array = ft_strsplit(s, ' ');
	len = array_length(array);
	if (len == 3)
	{
		while (i < len)
			mesh->indices[mesh->ind_pos++] = ft_atoi(array[i++]) - 1;
	}
	else if (len == 4)
	{
		while (i < 3)
			mesh->indices[mesh->ind_pos++] = ft_atoi(array[i++]) - 1;
		mesh->indices[mesh->ind_pos++] = ft_atoi(array[0]) - 1;
		mesh->indices[mesh->ind_pos++] = ft_atoi(array[2]) - 1;
		mesh->indices[mesh->ind_pos++] = ft_atoi(array[3]) - 1;
	}
}

void				get_mesh(int fd, t_sizes *sizes, t_mesh *mesh)
{
	char			*line;
	char			*token;

	lseek(fd, 0, SEEK_SET);
	allocate_mesh(mesh, sizes);
	while (get_next_line(fd, &line))
	{
		token = get_first_token(line);
		if (!ft_strcmp(token, "v"))
			add_vertices(mesh, line);
		else if (!ft_strcmp(token, "f"))
			add_face(mesh, line);
		free(token);
		free(line);
	}
	free(line);
}

void				calc_center(t_mesh *m)
{
	m->center.x = m->mm.min_x + ABS(m->mm.max_x - m->mm.min_x) / 2;
	m->center.y = m->mm.min_y + ABS(m->mm.max_y - m->mm.min_y) / 2;
	m->center.z = m->mm.min_z + ABS(m->mm.max_z - m->mm.min_z) / 2;
}

t_mesh				*parse_obj(char *filename)
{
	int				fd;
	t_sizes			*sizes;
	t_mesh			*mesh;

	if ((fd = open(filename, O_RDONLY)) == -1) {
		return (NULL);
	}
	if (!(sizes = (t_sizes *)malloc(sizeof(t_sizes))))
		return (NULL);
	ft_bzero(sizes, sizeof(t_sizes));
	get_array_sizes(fd, sizes);
	if (!(mesh = (t_mesh *)malloc(sizeof(t_mesh))))
		return (NULL);
	init_min_max(mesh);
	get_mesh(fd, sizes, mesh);
	calc_center(mesh);
	mesh->pos.x = 0;
	mesh->pos.y = 0;
	mesh->pos.z = -5;
	return (mesh);
}
