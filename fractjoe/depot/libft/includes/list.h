/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 10:34:52 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/12 14:37:10 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct			s_list
{
	void				*data;
	struct s_list		*next;
}						t_list;

void					ft_create_list(t_list **list, void *data);
void					ft_free_list(t_list *list);
#endif
