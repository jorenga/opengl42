/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:59:24 by jrenouf-          #+#    #+#             */
/*   Updated: 2013/12/26 13:43:25 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_power(int n)
{
	int		res;

	res = 1;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		res *= 10;
	}
	return (res);
}

static void	ft_whatsign(char *str, int *n, int *i)
{
	if (*n < 0)
	{
		str[0] = '-';
		*n = *n * (-1);
		*i = *i + 1;
	}
}

static int	ft_whatlen(int n)
{
	int		len;

	len = 0;
	while (n > 9 || n < (-9))
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		pow;
	int		nlen;
	int		i;

	i = 0;
	pow = ft_power(n);
	nlen = ft_whatlen(n);
	if ((str = ft_strnew(nlen + 4)) == NULL)
		return (NULL);
	if (n == (-2147483648))
	{
		str = ft_strnew(11);
		ft_strcpy(str, "-2147483648");
		return (str);
	}
	ft_whatsign(str, &n, &i);
	while (pow != 0)
	{
		str[i++] = (n / pow) + '0';
		n = n % pow;
		pow = pow / 10;
	}
	return (str);
}
