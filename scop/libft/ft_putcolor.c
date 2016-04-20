/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenouf- <jrenouf-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 14:28:03 by jrenouf-          #+#    #+#             */
/*   Updated: 2014/03/05 17:47:25 by jrenouf-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"

void		ft_putstr_color(char *s, char c)
{
	if (c == 'R')
	{
		ft_putstr("\033[31m");
		ft_putstr(s);
		ft_putstr("\033[00m");
	}
	if (c == 'G')
	{
		ft_putstr("\033[32m");
		ft_putstr(s);
		ft_putstr("\033[00m");
	}
	if (c == 'Y')
	{
		ft_putstr("\033[33m");
		ft_putstr(s);
		ft_putstr("\033[00m");
		ft_putendl("");
	}
	if (c == 'B')
	{
		ft_putstr("\033[36m");
		ft_putstr(s);
		ft_putstr("\033[00m");
	}
}
