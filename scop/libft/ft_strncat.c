/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 10:06:09 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/12/26 15:28:38 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t		size_s1;
	size_t		size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (size_s2 > n)
	{
		ft_memcpy(s1 + size_s1, s2, n);
		s1[size_s1 + n] = '\0';
	}
	else
		ft_strcat(s1, s2);
	return (s1);
}
