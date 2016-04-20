/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 15:33:26 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/26 15:48:59 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (ft_strlen(s2) < n)
	{
		while (i != ft_strlen(s2))
		{
			s1[i] = s2[i];
			i++;
		}
		while (s1[i] != '\0')
		{
			s1[i] = '\0';
			i++;
		}
	}
	else
	{
		while (i != n)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	return (s1);
}
