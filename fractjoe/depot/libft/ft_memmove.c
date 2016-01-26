/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:04:29 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/25 13:42:27 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * n);
	if (tmp == NULL)
	{
		return (0);
	}
	ft_memcpy(tmp, s2, n);
	ft_memcpy(s1, tmp, n);
	free(tmp);
	return (s1);
}
