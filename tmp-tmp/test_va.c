#include <stdarg.h>
#include <stdio.h>

int	ft_printf(const char *format, ...)
{
	va_list ap;
	char c;

	va_start(ap, format);

	c = (char)va_arg(ap, int);

	printf("%c\n",c);

	va_end(ap);

}


int main(void)
{
	ft_printf("test",'a');
}
