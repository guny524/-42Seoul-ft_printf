/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 22:13:59 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/05 19:19:22 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

char	*str_chr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

int	state_normal(t_print *print)
{
	t_print	save;

	if (*print->format == '%')
		return (STATE_CONVERSION);
	if (print->check) // 실제 출력은 안 하고 width(print->size) 조건 충족하는지 먼저 시뮬레이션
		save = *print;
	general_write(print, print->format, 1);
	if (print->check) // 시뮬레이션 끝나고 print 정보 다시 복구
	{
		if (-1 == print->ret)
			return (STATE_ERROR);
		*print = save;
		print->format--; // run_print()의 반복문에서 증가될거기 때문에 미리 빼줘야 함
		print->check = 0;
		return (STATE_NORMAL);
	}
	return (STATE_NORMAL);
}

int	state_conversion(t_print *print)
{
	t_print	save;

	if (print->check) // 실제 출력은 안 하고 width(print->size) 조건 충족하는지 먼저 시뮬레이션
		save = *print;
	if (*print->format == '%')
		general_write(print, "%", 1);
	else if (*print->format == 'c')
		print_char(print);
	else if (*print->format == 's')
		print_str(print);
	else if (str_chr("diuxXp", *print->format))
		conversion_num(print);
	if (print->check) // 시뮬레이션 끝나고 print 정보 다시 복구
	{
		if (-1 == print->ret)
			return (STATE_ERROR);
		*print = save;
		print->format--; // run_print()의 반복문에서 증가될거기 때문에 미리 빼줘야 함
		print->check = 0;
		return (STATE_CONVERSION);
	}
	return (STATE_NORMAL);
}
