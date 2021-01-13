/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parts_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saoki <saoki@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 14:34:02 by saoki             #+#    #+#             */
/*   Updated: 2020/12/30 14:41:46 by saoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strlen(const char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	 count++;
	return (count);
}

int	printf_strchr(const char *s, char c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)s;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void printf_putchar(char c, int num)
{
	while (num--)
		write(1, &c, sizeof(char));
}

void	put_minus(long long num)
{
	if (num < 0)
	write(1, "-", 1);
}

/*　再帰部分とbaseの判定を分けたほうがいいかも
void putnbr_di(long long num)
{
	char	c;
	char	*base = "0123456789";

	if (num >= 10)
	{
		putnbr_di(num / 10);
	}
	c = base[num % 10];
	write(1, &c, sizeof(char));
}

void putnbr_ux(unsigned long long num, t_data_flag data)
{
	unsigned int	size;
	char	c;
	char	*base;

	if (data.specifier == SPEC_SX || data.specifier == SPEC_P)
	{
		base = "0123456789abcdef";
		size = 16;
	}
	else if (data.specifier == SPEC_LX)
	{
		base = "0123456789ACDEF";
		size = 16;
	}
	else
	{
		base = "0123456789";
		size = 10;
	}

	if (num >= size)
	{
		putnbr_ux(num / size, data);
	}
	c = base[num % size];
	write(1, &c, sizeof(char));
}
*/

void print_digit_re(unsigned long long n, char *base, unsigned int size)
{
	char c;

	if (n >= size)
		print_digit_re(n / size, base, size);
	c = base[n % size];
	write(1, &c, sizeof(char));
}

void putnbr_diux(unsigned long long num, t_data_flag data)
{
	if (data.specifier == SPEC_SX || data.specifier == SPEC_P)
		print_digit_re(num, "0123456789abcdef", 16);
	else if (data.specifier == SPEC_LX)
		print_digit_re(num, "0123456789ABCDEF", 16);
	else
		print_digit_re(num, "0123456789", 10);
}

/*
int get_digit_di(long long num, t_data_flag data)
{
	int	i;
	unsigned long long	n;

	i = 0;
	if (num < 0)
		n = -num;
	else
		n = num;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	if (num == 0 && data.precision != 0)
		i = 1;
	return (i);
}


int get_digit_ux(unsigned long long num, t_data_flag data)
{
	int	i;

	i = 0;
	while (num > 0)
	{
		i++;
		if (data.specifier == SPEC_U)
			num /= 10;
		else
			num /= 16;
	}
	if (num == 0 && data.precision != 0)
		i = 1;
	return (i);
}
*/

int get_digit_di(long long num)
{
	int	i;
	unsigned long long	n;

	i = 0;
	if (num < 0)
		n = -num;
	else
		n = num;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}


int get_digit_ux(unsigned long long num, t_data_flag data)
{
	int	i;

	i = 0;
	while (num > 0)
	{
		i++;
		if (data.specifier == SPEC_U)
			num /= 10;
		else
			num /= 16;
	}
	return (i);
}
