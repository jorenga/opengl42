/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 17:12:48 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/26 15:52:12 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	int		len;
	char	*str;

	len = ft_strlen(s2);
	str = (char *)s1;
	if (*s2 == '\0')
		return ((char *)s1);
	while (*str != '\0')
	{
		if (ft_memcmp(str, s2, len) == 0)
				return (str);
		str++;
	}
	return (NULL);
}
