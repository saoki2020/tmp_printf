#include <stdio.h>

int	main(void)
{
	int		i;
	unsigned int	oux;
	char		c;
	char		*s;

	i = 12345;
	oux = 12345;
	c = '1';
	s = "12345";

	printf("[%10.0d]\n",0);
	printf("abcdefg\n");
	printf("[%-10.6d]\n",i);
	printf("[%-10.6s]\n",s);
	printf("[%-10.4d]\n",i);
	printf("[%-10.4s]\n",s);

	printf("[%i]\n",i);
	printf("[%o]\n",oux);
	printf("[%u]\n",oux);
	printf("[%x]\n",oux);
	printf("[%c]\n",c);
}
