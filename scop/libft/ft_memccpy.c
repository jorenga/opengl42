/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:11:16 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/26 15:36:24 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	char		*str1;
	const char	*str2;
	int			i;

	i = 0;
	str1 = (char *)s1;
	str2 = (const char *)s2;
	while (n > 0)
	{
		str1[i] = str2[i];
		if (str2[i] == c)
			return (s1 + (i + 1));
		i++;
		n--;
	}
	return (NULL);
}
