/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 23:16:09 by saoki             #+#    #+#             */
/*   Updated: 2021/01/03 23:16:33 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int	print_data(const char **start, const char **fmt,
va_list *ap, t_data_flag *data)
{
	if (data->specifier == -1)
		return (print_non_specifier(start, fmt, data));
	(*fmt)++;
if (data->specifier == SPEC_D || data->specifier == SPEC_I)
	print_int(ap, data);
else if (data->specifier >= SPEC_U && data->specifier <= SPEC_LX)
	print_unsigned(ap, data);
else if (data->specifier == SPEC_C)
	print_char(ap, data);
else if (data->specifier == SPEC_S)
	print_string(ap, data);
else if (data->specifier == SPEC_P)
	print_pointer(ap, data);
else
	print_persent(data);
return (data->ordi_len + data->spec_len + data->field);
}



int	print_non_specifier(const char **start, const char **fmt,
t_data_flag *data)
{
	if (!**fmt)
		return (-1);
	data->spec_len = *fmt - *start;
	write(1, *start, data->spec_len);
	return (data->ordi_len + data->spec_len);
}

void print_persent(t_data_flag *data)
{
	size_t zero_len;
	data->spec_len = 1;
	data->field = (data->field <= data->spec_len ? 0 : data->field - data->spec_len);
	if (!data->flag[FLAG_MINUS] && !data->flag[FLAG_ZERO])
		printf_putchar(' ', data->field);
	zero_len = (!data->flag[FLAG_MINUS] && data->flag[FLAG_ZERO] ? data->field : 0);
	printf_putchar('0', zero_len);
	write (1, "%%", 1);
	if (data->flag[FLAG_MINUS])
		printf_putchar(' ', data->field);
}
