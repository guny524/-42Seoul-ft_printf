/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 02:04:09 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/06 16:25:24 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

uintmax_t	str_len(char *str)
{
	uintmax_t	cnt;

	cnt = 0;
	while (*str)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

/*
* conversino_num에서 한 줄로 구조체 초기화하기 위한 함수
*/
t_data	new_data(int sign, size_t size, char *base)
{
	t_data	data;

	data.sign = sign;
	data.size = size;
	data.base = base;
	data.base_len = str_len(base);
	return (data);
}

/*
* 보통 duxXp 별로 함수를 따로 만들지만 보면 print_num 함수 하나의 로직으로 해결함
* 출력할 숫자의 sign여부, byte size, 진수 정보만 알고 있으면 비트연산자로 하나의 로직으로 출력 가능
*/
void	conversion_num(t_print *print)
{
	t_data	data;

	if (*print->format == 'd' || *print->format == 'i')
		data = new_data(1, sizeof(int), "0123456789");
	else if (*print->format == 'u')
		data = new_data(0, sizeof(unsigned int), "0123456789");
	else if (*print->format == 'x')
		data = new_data(0, sizeof(unsigned int), "0123456789abcdef");
	else if (*print->format == 'X')
		data = new_data(0, sizeof(unsigned int), "0123456789ABCDEF");
	else if (*print->format == 'p')
	{
		general_write(print, "0x", 2);
		if (-1 == print->ret)
			return ;
		data = new_data(0, sizeof(void *), "0123456789abcdef");
	}
	data.num = va_arg(print->ap, uintmax_t);
	return (print_num(print, &data));
}
