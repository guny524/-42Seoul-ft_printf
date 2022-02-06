/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:37:08 by min-jo            #+#    #+#             */
/*   Updated: 2021/12/09 22:39:37 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

int	print_char(char c)
{
	return (write(1, &c, 1));
}

int	print_str(va_list *ap)
{
	char	*str;
	char	*ret;

	str = va_arg(*ap, char *);
	if (str == NULL)
		return (write(1, "(null)", 6));
	ret = str;
	while (*str)
		write(1, str++, 1);
	return (str - ret);
}
