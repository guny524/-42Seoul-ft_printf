/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:35:41 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/06 17:36:32 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

/*
* size로 0b10000 꼴인 minus_mask와 0b11111꼴인 bit_mask 계산
*/
void	cal_mask(size_t size, uintmax_t *bit_mask, uintmax_t *minus_mask)
{
	size_t		bit_size;

	bit_size = 8 * size;
	*bit_mask = 0b0U;
	while (bit_size--)
		*bit_mask = (*bit_mask << 1) | 0b1;
	*minus_mask = 0b1U;
	*minus_mask <<= (8 * size - 1);
}

/*
* 숫자 표현 범위 내 base_len^지수승 꼴의 최대 값을 구함
* 4byte int 면 2147483647이 최대 숫자고 10^지수승 꼴 최대값은 1000000000임
* 이게 base_len과 byte에 따라 달라지니까 계산해줘야 됨
*/
uintmax_t	cal_divnum(t_data *data, uintmax_t max)
{
	uintmax_t	divnum;

	max >>= data->sign;
	divnum = 0b1U;
	while (divnum * data->base_len < max && divnum * data->base_len > divnum)
		divnum *= data->base_len;
	return (divnum);
}

/*
* 단순한 양수 정수 출력
*/
void	print_num_pos(t_print *print, t_data *data, uintmax_t divnum)
{
	while (data->num < divnum && 1 < divnum)
		divnum /= data->base_len;
	while (divnum)
	{
		general_write(print, data->base + data->num / divnum, 1);
		if (-1 == print->ret)
			return ;
		data->num %= divnum;
		divnum /= data->base_len;
	}
}

/*
* print->num 숫자를 write 시스템 콜만 사용하여 출력
* data 구조체를 보면 num의 signed여부, byte size, base_len을 알면 출력 가능
* 1. -2147483648 절댓값 1줄이고 2의 보수 계산
* 2. 2147483647 맨 앞 한자리 2만 출력, 나머지 저장
* 3. 147483647 절댓값 1늘려서 다시 원래 숫자 복원
* 4. 147483648 양수 출력 로직으로 넘김
*/
void	print_num(t_print *print, t_data *data)
{
	uintmax_t	bit_mask;
	uintmax_t	minus_mask;
	uintmax_t	divnum;

	cal_mask(data->size, &bit_mask, &minus_mask);
	divnum = cal_divnum(data, bit_mask);
	data->num &= bit_mask;
	if (data->sign && (data->num & minus_mask))
	{
		general_write(print, "-", 1);
		if (-1 == print->ret)
			return ;
		data->num = (~(data->num + 1) + 1) & bit_mask;
		if (data->num / divnum)
		{
			general_write(print, data->base + data->num / divnum, 1);
			if (print->ret == -1)
				return ;
		}
		data->num = data->num % divnum + 1;
		divnum /= data->base_len;
	}
	print_num_pos(print, data, divnum);
}
