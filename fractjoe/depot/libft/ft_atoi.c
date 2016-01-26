/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 15:25:59 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/07 12:14:13 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_whatsign(const char *str)
{
	if (str[0] == '-')
		return (-1);
	else if (str[0] == '+')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	int			res;
	int			p;
	int			s;

	p = 10;
	s = 1;
	res = 0;
	while (*str == '\n' || *str == '\v' || *str == '\t' || *str == '\r'
			|| *str == '\f' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		s = ft_whatsign(str);
		str++;
	}
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			res = *str - '0' + res * p;
		else
			return (res * s);
		str++;
	}
	return (res * s);
}
