/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/08 11:31:32 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/12 14:35:53 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/list.h"

static t_list			*ft_create_link(void *data)
{
	t_list				*link;

	if ((link = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	link->data = data;
	link->next = NULL;
	return (link);
}

static void				ft_add_link(t_list *list, void *data)
{
	t_list				*link;

	link = ft_create_link(data);
	while (list->next != NULL)
		list = list->next;
	list->next = link;
}

void					ft_create_list(t_list **list, void *data)
{
	if ((*list) == NULL)
		(*list) = ft_create_link(data);
	else
		ft_add_link(*list, data);
}
