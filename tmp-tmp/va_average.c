#include <stdarg.h>
#include <string.h>
#include <stdio.h>

double average(char *s, ...)
{
	va_list	arg;
	va_start(arg,s);

	double sum;
	int len;
	int i;

	len = strlen(s);
	sum = 0;
	for (i = 0; i < len; i++)
	{
		sum += va_arg(arg, double);
	}
	va_end(arg);

	printf("%d\n",len);
	printf("%f\n",sum);

	return (sum/len);
}

int	main(void)
{
	double x;
	x = average("123",1.0,2.0,3.0);
	printf("%f\n",x);
}
