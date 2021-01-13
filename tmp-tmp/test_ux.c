#include <stdio.h>

int main(void)
{
	unsigned int num = 100;
	int i;
	int j;

	i = printf("[%10x]\n",num);
	j = printf("[%#10x]\n",num);
	printf("%d\n",i-3);
	printf("%d\n",j-3);

	i = printf("[%.5x]\n",num);
	j = printf("[%#.5x]\n",num);
	printf("%d\n",i-3);
	printf("%d\n",j-3);

	i = printf("[%10.5x]\n",num);
	j = printf("[%#10.5x]\n",num);
	printf("%d\n",i-3);
	printf("%d\n",j-3);
}
