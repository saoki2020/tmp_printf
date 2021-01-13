#include <stdio.h>

int main(void)
{
	int i,n,f,k;
 unsigned long long minus;


	i = 0;
	printf("%.d\n",i);
	printf("%p\n",&i);
	n = printf("%.p\n",0);
	printf("%d\n",n - 1);


f = printf("[%p]\n",(unsigned long long)0);
    printf("%d\n",f);

k = printf("[%-30.20p]\n", minus);
    printf("%d\n",k);
}
