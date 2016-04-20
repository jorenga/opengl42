#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/time.h>
# include "struct.h"
# include "libft.h"

t_mesh				*parse_obj(char *filename);

#endif
