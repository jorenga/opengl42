# include "parsing.h"

void				print_time(double t)
{
	int				m, s, ms, us;

	m = (int)(t / 60000000);
	s = (int)(t / 1000000) % 60;
	ms = (int)(t / 1000) % 1000;
	us = (int)t % 1000;
	printf("Parsing time: %dm%ds%dms%dus\n", m, s, ms, us);
}

long unsigned int		get_time()
{
	struct timeval		t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000000 + t.tv_usec);
}

char				*get_first_token(char *str)
{
	int				i;
	int				j;
	char			*token;
	
	if ((token = (char *)malloc(sizeof(char) * 64)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] == 32)
		i++;
	while (str[i] != '\0' && str[i] != 32 && str[i] != '\t')
	{
		token[j] = str[i];
		i++;
		j++;
	}
	token[j] = '\0';
	return (token);
}

int					array_length(char **array)
{
	int				i;

	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

int					get_nb_ind(char *line)
{
	int				nb;
	char			**tab;

	tab = ft_strsplit(line, ' ');
	nb = array_length(tab);
	return (nb - 1);
}

void				get_array_sizes(int fd, t_sizes *sizes)
{
	char			*line;
	char			*token;

	while (get_next_line(fd, &line))
	{
		token = get_first_token(line);
		if (!ft_strcmp(token, "v"))
			sizes->vert_size++;
		else if (!ft_strcmp(token, "vn"))
			sizes->norm_size++;
		else if (!ft_strcmp(token, "vt"))
			sizes->text_size++;
		else if (!ft_strcmp(token, "f"))
			sizes->ind_size += get_nb_ind(line);
		else if (!ft_strcmp(token, "s"))
		{
			if (!ft_strcmp(line, "s on"))
				sizes->smoothing = 1;
		}
		free(token);
		free(line);
	}
	free(line);
}

void				allocate_mesh(t_mesh *mesh, t_sizes *sizes)
{
	mesh->vertices = malloc(sizeof(t_vec4) * sizes->vert_size);
	mesh->normals =  malloc(sizeof(t_vec3) * sizes->norm_size);
	mesh->textures = malloc(sizeof(t_vec3) * sizes->text_size);
	mesh->indices =  malloc(sizeof(int) * sizes->ind_size);
	mesh->vert_pos = 0;
	mesh->norm_pos = 0;
	mesh->text_pos = 0;
	mesh->ind_pos = 0;
}

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

char				*get_faces(char *s)
{
	int				i;
	char			*str;

	i = 0;
	while (s[i] == 'f' || s[i] == ' ')
		i++;
	if ((str = malloc(sizeof(char) * (ft_strlen(s) - i) + 1)) == NULL)
		return (NULL);
	str = s + i;
	return (str);
}

void				add_face1(t_mesh *mesh, char *line)
{
	char			*s;
	char			**array;
	int				i;

	i = 0;
	s = get_faces(line);
	array = ft_strsplit(s, ' ');
	while (array[i] != NULL)
	{
		mesh->indices[mesh->ind_pos] = ft_atoi(array[i]) - 1;
		mesh->ind_pos++;
		i++;
	}
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

void				print_sizes(t_sizes *sizes)
{
	printf("nb vertices:\t%d\nnb normals:\t%d\nnb textures:\t%d\nnb indices:\t%d\nsmoothing:\t%s\n",
			sizes->vert_size, sizes->norm_size, sizes->text_size,
			sizes->ind_size, (sizes->smoothing) ? "true" : "false");
}
/*
static void				print_mesh(t_mesh *mesh)
{
	int				i;

	i = 0;
	while (i < mesh->vert_pos)
	{
		printf("v: %f\t%f\t%f\t%f\n", mesh->vertices[i].x, mesh->vertices[i].y, mesh->vertices[i].z, mesh->vertices[i].w);
		i++;
	}
	i = 0;
	while (i < mesh->ind_pos)
	{
		printf("i: %d\n", mesh->indices[i]);
		i++;
	}
}
*/
void				init_min_max(t_mesh *m)
{
	m->mm.min_x = 10000;
	m->mm.max_x = -10000;
	m->mm.min_y = 10000;
	m->mm.max_y = -10000;
	m->mm.min_z = 10000;
	m->mm.max_z = -10000;
}

# define ABS(x) ((x > 0) ? x : x * -1)

void				calc_center(t_mesh *m)
{
	m->center.x = m->mm.min_x + ABS(m->mm.max_x - m->mm.min_x) / 2;
	m->center.y = m->mm.min_y + ABS(m->mm.max_y - m->mm.min_y) / 2;
	m->center.z = m->mm.min_z + ABS(m->mm.max_z - m->mm.min_z) / 2;
	printf("x:\t%f-%f\ny:\t%f-%f\nz:\t%f-%f\n", m->mm.min_x, m->mm.max_x, m->mm.min_y, m->mm.max_y, m->mm.min_z, m->mm.max_z);
}

extern int errno;

t_mesh				*parse_obj(char *filename)
{
	int				fd;
	t_sizes			*sizes;
	t_mesh			*mesh;
	char			cwd[1024];

printf("cwd: %s\n", getcwd(cwd, sizeof(cwd)));
	if ((fd = open(filename, O_RDONLY)) == -1) {
		printf("file failed to open: %s\n", strerror(errno));
		return (NULL);
	}
	if (!(sizes = (t_sizes *)malloc(sizeof(t_sizes))))
		return (NULL);
	ft_bzero(sizes, sizeof(t_sizes));
	get_array_sizes(fd, sizes);
	if (!(mesh = (t_mesh *)malloc(sizeof(t_mesh))))
		return (NULL);
	init_min_max(mesh);
//	print_sizes(sizes);
	get_mesh(fd, sizes, mesh);
	calc_center(mesh);
//	print_mesh(mesh);
	mesh->pos.x = 0;
	mesh->pos.y = 0;
	mesh->pos.z = -10;
	return (mesh);
}
