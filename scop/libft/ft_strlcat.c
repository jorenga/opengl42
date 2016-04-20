/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 10:27:23 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/12/26 13:44:38 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		dlen;
	size_t		res;

	i = 0;
	dlen = ft_strlen(dst);
	res = dlen + ft_strlen(src);
	if (size == 0)
		return (ft_strlen(src));
	while (dlen < size - 1 && src[i] != '\0')
	{
		dst[dlen] = src[i];
		i++;
		dlen++;
	}
	dst[dlen] = '\0';
	if (size < ft_strlen(dst))
		return (size + ft_strlen(src));
	return (res);
}
