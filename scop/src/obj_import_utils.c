#include "obj_import.h"

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
	nb--;
	if (nb == 3)
		return (nb);
	return (6);
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
		else if (!ft_strcmp(token, "f"))
			sizes->ind_size += get_nb_ind(line);
		free(token);
		free(line);
	}
	free(line);
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
