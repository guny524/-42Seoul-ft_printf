/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:17:48 by min-jo            #+#    #+#             */
/*   Updated: 2021/12/10 19:40:42 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

typedef enum e_state
{
	STATE_ERROR = -1,
	STATE_NORMAL,
	STATE_CONVERSION,
}t_state;

int			print_char(char c);
int			print_str(va_list *ap);

int			ft_strlen(char *str);
void		cal_mask(size_t size, uintmax_t *bit_mask, uintmax_t *minus_mask);
uintmax_t	cal_divnum(int sign, uintmax_t max, uintmax_t base_len);
int			print_num(uintmax_t num, int sign, size_t size, char *base);
int			print_num_pos(uintmax_t num, uintmax_t divnum, char *base,
				int base_len);

int			state_normal(const char *format, int *cnt);
int			state_conversion(va_list *ap, const char *format, int *cnt);
int			conversion(va_list *ap, const char *format);
int			ft_printf(const char *format, ...);

#endif
