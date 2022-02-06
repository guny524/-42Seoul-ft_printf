/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:18:07 by min-jo            #+#    #+#             */
/*   Updated: 2021/12/09 22:49:30 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	conversion(va_list *ap, const char *format)
{
	if (*format == 'c')
		return (print_char(va_arg(*ap, int)));
	else if (*format == 's')
		return (print_str(ap));
	else if (*format == 'p')
	{
		write(1, "0x", 2);
		return (2 + print_num(va_arg(*ap, uintmax_t), 0, sizeof(void *),
				"0123456789abcdef"));
	}
	else if (*format == 'd' || *format == 'i')
		return (print_num(va_arg(*ap, uintmax_t), 1, sizeof(int),
				"0123456789"));
	else if (*format == 'u')
		return (print_num(va_arg(*ap, uintmax_t), 0, sizeof(unsigned int),
				"0123456789"));
	else if (*format == 'x')
		return (print_num(va_arg(*ap, uintmax_t), 0, sizeof(unsigned int),
				"0123456789abcdef"));
	else if (*format == 'X')
		return (print_num(va_arg(*ap, uintmax_t), 0, sizeof(unsigned int),
				"0123456789ABCDEF"));
	else if (*format == '%')
		return (write(1, "%", 1));
	return (-1);
}

int	state_normal(const char *format, int *cnt)
{
	int	ret;

	if (*format == '%')
		return (STATE_CONVERSION);
	ret = write(1, format, 1);
	if (ret == -1)
		return (STATE_ERROR);
	*cnt += ret;
	return (STATE_NORMAL);
}

int	state_conversion(va_list *ap, const char *format, int *cnt)
{
	int	ret;

	ret = conversion(ap, format);
	if (ret == -1)
		return (STATE_ERROR);
	*cnt += ret;
	return (STATE_NORMAL);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		cnt;
	t_state	state;

	cnt = 0;
	state = STATE_NORMAL;
	va_start(ap, format);
	while (*format)
	{
		if (state == STATE_ERROR)
		{
			va_end(ap);
			return (-1);
		}
		else if (state == STATE_NORMAL)
			state = state_normal(format, &cnt);
		else if (state == STATE_CONVERSION)
			state = state_conversion(&ap, format, &cnt);
		format++;
	}
	va_end(ap);
	return (cnt);
}
