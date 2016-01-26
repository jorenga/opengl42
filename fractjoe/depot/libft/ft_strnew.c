/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 16:11:28 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/26 15:49:47 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (size + 4));
	if (str == NULL)
		return (NULL);
	while (i < (size + 4))
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}
