/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 16:42:41 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/26 15:50:10 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int		len;

	len = ft_strlen((char *)s);
	while (len >= 0)
	{
		if (s[len] == c)
			return ((char *)(s + len));
		len--;
	}
	return (0);
}
