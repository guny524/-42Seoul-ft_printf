/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 12:33:24 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/05 19:26:47 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(t_print *print)
{
	char	c;

	c = va_arg(print->ap, int);
	general_write(print, &c, 1);
}

void	print_str(t_print *print)
{
	char	*str;

	str = va_arg(print->ap, char *);
	if (NULL == str)
	{
		general_write(print, "(null)", 6);
		return ;
	}
	while (*str)
	{
		general_write(print, str++, 1);
		if (-1 == print->ret)
			return ;
	}
}
