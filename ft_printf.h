/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: min-jo <min-jo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:17:48 by min-jo            #+#    #+#             */
/*   Updated: 2022/02/05 19:15:12 by min-jo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

/*
* 현재 진행하고 있는 print의 상태를 나타냄
*/
typedef enum e_state
{
	STATE_ERROR = -1,
	STATE_NORMAL,
	STATE_CONVERSION,
}	t_state;

/*
* print할 숫자에 대한 data
*/
typedef struct s_data
{
	uintmax_t	num;
	int			sign;
	size_t		size;
	char		*base;
	uintmax_t	base_len;
}	t_data;

/*
* 현재 진행하고 있는 print에 대한 정보
*/
typedef struct s_print
{
	char		*buf;	// 버퍼 출력이면 양수, 바로 출력이면 NULL
	int			fd;		// 버퍼 출력이면 -1, 바로 출력이면 양수
	size_t		size;	// 기본 INT_MAX+1로 설정
						// 한 번 print에 전체 cnt가 size 넘으면 -1 리턴
	const char	*format;
	size_t		cnt;
	va_list		ap;
	int			check;	// 1이면 cnt만 셈, 0이면 실제 출력
	int			ret;
}	t_print;

typedef struct s_field //# 보너스 파트를 위한 구조체, 아직 구현 안 함
{
	int	width;
	int	flag;
}	t_field;

/*
** ft_printf.c
*/
int			ft_printf(const char *format, ...);
int			general_printf(int fd, size_t size, char *str, ...);
t_print		init_print(int fd, size_t size, char *str, va_list ap);
int			run_print(t_print print);
void		general_write(t_print *print, const char *buf, size_t nbyte);
/*
** state.c
*/
char		*str_chr(const char *s, int c);
int			state_normal(t_print *print);
int			state_conversion(t_print *print);
/*
** print_char.c
*/
void		print_char(t_print *print);
void		print_str(t_print *print);
/*
** conversion_num.c
*/
uintmax_t	str_len(char *str);
t_data		new_data(int sign, size_t size, char *base);
void		conversion_num(t_print *print);
/*
** print_num.c
*/
void		cal_mask(size_t size, uintmax_t *bit_mask, uintmax_t *minus_mask);
uintmax_t	cal_divnum(t_data *data, uintmax_t max);
void		print_num(t_print *print, t_data *data);
void		print_num_pos(t_print *print, t_data *data, uintmax_t divnum);

#endif
