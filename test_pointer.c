#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
 int i,j,k,f;
	int n = 0;

	printf("[%d][%x][%p][%%]\n",31,31,&n);
 printf("[%p][%x][%d][%%]\n",&n,31,31);

	i = ft_printf("[%p]\n", &n);
	j = printf("[%p]\n", &n);
	printf("%d\n",i-3);
	printf("%d\n",j-3);

 k = ft_printf("[%.0p]\n", 0);
	f = printf("[%.0p]\n", 0);
	printf("%d\n",k-3);
	printf("%d\n",f-3);

 k = ft_printf("[%30.20p]\n", &n);
	f = printf("[%30.20p]\n", &n);
	printf("%d\n",k-3);
	printf("%d\n",f-3);

 k = ft_printf("[%*.*p]\n",-30, 20, &n);
	f = printf("[%*.*p]\n",-30, 20, &n);
	printf("%d\n",k-3);
	printf("%d\n",f-3);
}
