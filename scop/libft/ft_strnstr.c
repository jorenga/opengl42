/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 11:42:29 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/02/05 13:45:12 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s2);
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] != '\0')
	{
		if (i + len <= n && ft_memcmp((s1 + i), s2, len) == 0)
			return ((char *)(s1 + i));
		i++;
	}
	return (NULL);
}
