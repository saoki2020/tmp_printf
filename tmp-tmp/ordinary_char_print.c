#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
void	ft_print_str(const char **start, const char **format, int *n)
{
	while (**format != '%' && **format)
			(*format)++;
	write(1, *start, *format - *start);
	*n += *format - *start;
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int		n;
	const char	*start;

	n = 0;
	va_start(ap, format);
	if (format == NULL)
		n = -1;
	while (n >= 0 && *format)
	{
		start = format;
		if (*start != '%')
			ft_print_str(&start, &format, &n);
		else
			return (0);
	}
	va_end(ap);
	return (n);
}

int	main(void)
{
	ft_printf("abcdefg%d\n",0);
}
