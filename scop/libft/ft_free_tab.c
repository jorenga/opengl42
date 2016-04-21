/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 13:46:01 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/04 13:47:27 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void				ft_free_tab(char **tab)
{
	int				i;

	i = 0;
	while (tab[i] != NULL)
		free(tab[i++]);
	free(tab);
}