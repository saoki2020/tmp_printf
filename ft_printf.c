/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 08:45:13 by saoki             #+#    #+#             */
/*   Updated: 2020/12/30 08:45:42 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_field(const char **fmt, va_list *ap, t_data_flag *data)
{
	int num;
//指定してなければ０
	num = 0;
	//.の次が＊だったら、apに入ってる引数からintのやつを読み取る
	if (**fmt == '*')
	{
		num = va_arg(*ap, int);

		//＊を表す引数が負の値=>「-」フラグと正の数ってことになる
		if (num < 0)
		{
			num *= -1;
			data->flag[FLAG_MINUS] = 1;
		}
		(*fmt)++;
	}
	//fmtのアドレスを一つ進めて、それが数字だったら
	else if (ft_isdigit(**fmt))
	{
//[数字]を[数値に変換]。
		while (ft_isdigit(**fmt))
			num = num * 10 + (*((*fmt)++) - '0');
	}
	return (num);
}

int get_precision(const char **fmt, va_list *ap)
{
	int num;

//指定していない場合：-1とする
	num = -1;
//.の次が＊だったら引数を読み取る
	if (**fmt == '*')
	{
		num = va_arg(*ap, int);
		if (num < 0)
			num = -1;
	(*fmt)++;
	}
	//.の次が数字だったら数字を読み取る
	else if (ft_isdigit(**fmt))
	{
		num = 0;
		while (ft_isdigit(**fmt))
			num = num * 10 + (*((*fmt)++) - '0');
	}
	//.だけの時は精度は0
 	else if (!ft_isdigit(**fmt))
		num = 0;
	return (num);
}

void	initialize_data(t_data_flag	*data, int	n)
{
	data->flag[FLAG_ZERO] = 0;
	data->flag[FLAG_MINUS] = 0;
	data->flag[FLAG_SHARP] = 0;
	data->field = 0;
	data->precision = -1;
	data->specifier = -1;
	data->ordi_len = (n < 0 ? 0 : n);
	data->spec_len = 0;
}

void	print_ordinary_str(const char **start, const char **fmt, int *n)
{
	while (**fmt != '%' && **fmt)
			(*fmt)++;
	write(1, *start, *fmt - *start);
	*n += *fmt - *start;
}

void	print_specifier_str(const char	**start, const char	**fmt,	int	*n,
	va_list	*ap)
{
	int	num;
	t_data_flag	data;

	(*fmt)++;
	initialize_data(&data, *n);
	while ((num = printf_strchr("#0- +", **fmt)) >= 0)
	{
		data.flag[num] = 1;
		(*fmt)++;
	}
	data.field = get_field(fmt, ap, &data);
	if (**fmt == '.')
	{
		(*fmt)++;
		data.precision = get_precision(fmt, ap);
	}
 data.specifier = printf_strchr("diuxXcsp%", **fmt);
	num = print_data(start, fmt, ap, &data);
	*n = ((*n == 0 || num >= 0) ? num : *n);
}



int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		n;
	const char	*start;

	n = 0;
	va_start(ap, fmt);
	if (fmt == NULL)
		n = -1;
	while (n >= 0 && *fmt)
	{
		start = fmt;
		if (*start != '%')
			print_ordinary_str(&start, &fmt, &n);
		else
			print_specifier_str(&start, &fmt, &n, &ap);
	}
	va_end(ap);
	return (n);
}
