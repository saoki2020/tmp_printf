#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	int num1;
	int num2;
 int i = 0;
	int u = -11;

	num1 = ft_printf("printf1 = [%10.d]\n",i);
	num2 = printf("printf2 = [%10.d]\n",i);
	printf("printf1_output = [%d]\n",num1-13);
	printf("printf2_output = [%d]\n",num2-13);

	num1 = ft_printf("printf1 = [%*.*d]\n",10,5,u);
	num2 = printf("printf2 = [%*.*d]\n",10,5,u);
	printf("printf1_output = [%d]\n",num1-13);
	printf("printf2_output = [%d]\n",num2-13);

num1 = ft_printf("printf1 = [%*.*d]\n",-10,5,u);
num2 = printf("printf2 = [%*.*d]\n",-10,5,u);
printf("printf1_output = [%d]\n",num1-13);
printf("printf2_output = [%d]\n",num2-13);
}
