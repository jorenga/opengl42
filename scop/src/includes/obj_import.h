#ifndef OBJ_IMPORT_H
# define OBJ_IMPORT_H

# include <fcntl.h>
# include <stdio.h>
# include "struct.h"
# include "libft.h"

# define ABS(x) ((x > 0) ? x : x * -1)

t_mesh				*parse_obj(char *filename);

char				*get_first_token(char *str);
int					array_length(char **array);
int					get_nb_ind(char *line);
void				get_array_sizes(int fd, t_sizes *sizes);
char				*get_faces(char *s);

void				allocate_mesh(t_mesh *mesh, t_sizes *sizes);
void				init_min_max(t_mesh *m);

#endif
