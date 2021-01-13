#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	int i,j;
	char c = 0;

	i = ft_printf("[%10c]\n",'a');
	j = printf("[%10c]\n",'a');
	printf("%d\n",i-3);
	printf("%d\n",j-3);

	i = ft_printf("[%-10c]\n",'a');
	j = printf("[%-10c]\n",'a');
	printf("%d\n",i-3);
	printf("%d\n",j-3);

	i = ft_printf("[%c]\n",c);
	j = printf("[%c]\n",c);
	printf("%d\n",i-3);
	printf("%d\n",j-3);

	printf("%s\n",NULL);
}
