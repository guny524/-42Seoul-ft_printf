/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:35:41 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/06 15:11:09 by min-jo           ###   ########.fr       */
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
	*bit_mask = 0b0U; // 31비트 부분에서 << 연산자 하면 32숫자로 볼 지 64비트 숫자로 볼 지 undefined, U로 명시해준다.
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

	max >>= data->sign; // max로 0b11111 꼴인 bit_mask를 받아오는데, 이게 숫자 표현 범위 내 최대 값임, signed이면 맨 앞 한 칸 사용 안 함
	divnum = 0b1U;
	while (divnum * data->base_len < max && divnum * data->base_len > divnum)
	// 표현 가능한 최대 숫자 보다 작을 때 까지 반복
	// unsigned 변수 uintmax_t를 사용하기 때문에, base_len을 계속 곱하다 보면 오버플로날 수 있다.
	// 곱했는데 곱하기 전 숫자보다 커지지 않고, 작아지면 반복문 종료, 클 때 동안은 반복
		divnum *= data->base_len;
	return (divnum);
}

/*
* 단순한 양수 정수 출력
*/
void	print_num_pos(t_print *print, t_data *data, uintmax_t divnum)
{
	// divnum이 num보다 큰 경우 자리수를 맞추기 위해 줄여야 하는데
	// num == 0이면 출력은 되야 하니까, 1자리는 남김
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
	data->num &= bit_mask; // 변수는 uintmax_t로 8byte 변수쓰는데 num 값이 4byte만 저장될 수 있으므로 비트마스크로 걸러야 됨
	if (data->sign && (data->num & minus_mask)) // signed인데 맨 앞 비트가 1이면 음수이다
	{
		general_write(print, "-", 1); // 음수이기 때문에 일단 '-' 출력
		if (-1 == print->ret) // write에서 에러 났을 때 종료
			return ;
		// 음수를 uintmax_t unsigned 변수에 저장했으므로 나누기 연산이 안 됨
		// 음수를 2의 보수 계산하여 양수로 바꾼다.
		// 음수 제일 작은 숫자일 때 양수의 표현 범위를 넘으므로 일단 1을 더해서 절댓값을 줄이고 2의 보수로 만듬
		// 8byte 변수에 4byte 숫자가 저장됐을 수 있으므로 2의보수 변환 후 비트마스크로 걸러야 한다.
		data->num = (~(data->num + 1) + 1) & bit_mask;
		if (data->num / divnum) // 음수->양수, 이제 양수니까 나누기 연산 가능
		{
			// 맨 앞 숫자 한 자리만 출력, -2147483648이면 2만 출력한다.
			general_write(print, data->base + data->num / divnum, 1);
			if (print->ret == -1)
				return ;
		}
		// 절댓값을 1 줄인 후 양수로 만들고, divnum으로 나눈 나머지에 다시 1을 더해도 오버플로가 안 일어남
		// 절댓값을 1을 더해서 원래 수로 되돌려줌
		data->num = data->num % divnum + 1;
		divnum /= data->base_len;
	}
	print_num_pos(print, data, divnum); // 양수 출력으로 넘김
}
