/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 15:47:43 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/11/26 16:25:58 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char		*str;
	size_t		i;
	size_t		j;
	size_t		len;

	i = 0;
	j = 0;
	len = (ft_strlen(s) - 1);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	if ((s[0] == '\0') || (i == j && len == (ft_strlen(s) - 1)))
	{
		str = ft_strnew(ft_strlen(s));
		str = ft_strcpy(str, s);
		return (str);
	}
	str = ft_strnew(len - i + 1);
	if (str == NULL)
		return (NULL);
	while (i <= len)
		str[j++] = s[i++];
	return (str);
}
