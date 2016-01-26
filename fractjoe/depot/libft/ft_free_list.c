/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 14:14:23 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/12 14:37:10 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/list.h"

void				ft_free_list(t_list *list)
{
	t_list			*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
	free(list);
}
