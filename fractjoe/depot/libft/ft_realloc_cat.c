/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_cat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 13:43:52 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/04 13:54:01 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void				ft_realloc_cat(char **s1, char *s2)
{
	int				len;
	char			*str;

	len = ft_strlen(*s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * len);
	str = ft_strcpy(str, *s1);
	str = ft_strcat(str, s2);
	free(*s1);
	*s1 = str;
}
