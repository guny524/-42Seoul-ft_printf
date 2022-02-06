/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:35:41 by min-jo            #+#    #+#             */
/*   Updated: 2021/12/13 16:53:33 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>

int	str_len(char *str)
{
	int		cnt;

	cnt = 0;
	while (*str)
	{
		cnt++;
		str++;
	}
	return (cnt);
}

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

uintmax_t	cal_divnum(int sign, uintmax_t max, uintmax_t base_len)
{
	uintmax_t	divnum;

	max >>= sign;
	divnum = 0b1U;
	while (divnum * base_len < max && divnum * base_len > divnum)
		divnum *= base_len;
	return (divnum);
}

int	print_num_pos(uintmax_t num, uintmax_t divnum, char *base,
		int base_len)
{
	int	cnt;

	cnt = 0;
	while (num < divnum && 1 < divnum)
		divnum /= base_len;
	while (divnum)
	{
		write(1, base + num / divnum, 1);
		cnt++;
		num %= divnum;
		divnum /= base_len;
	}
	return (cnt);
}

int	print_num(uintmax_t num, int sign, size_t size, char *base)
{
	uintmax_t	base_len;
	uintmax_t	bit_mask;
	uintmax_t	minus_mask;
	uintmax_t	divnum;
	int			cnt;

	base_len = str_len(base);
	cal_mask(size, &bit_mask, &minus_mask);
	divnum = cal_divnum(sign, bit_mask, base_len);
	num &= bit_mask;
	cnt = 0;
	if (sign && (num & minus_mask))
	{
		write(1, "-", 1);
		cnt++;
		num = (~(num + 1) + 1) & bit_mask;
		if (num / divnum)
		{
			write(1, base + num / divnum, 1);
			cnt++;
		}
		num = num % divnum + 1;
		divnum /= base_len;
	}
	return (cnt + print_num_pos(num, divnum, base, base_len));
}
