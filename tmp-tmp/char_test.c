#include <stdio.h>

int main(void)
{
	char *s;
	s = "abcdefghijklmns";

	printf("[%.10s]\n",s);
	printf("[%020s]\n",s);
	printf("[%c]\n",'a');
	printf("[%10c]\n",'a');
	printf("[%*c]\n",10,'a');
	printf("[%-10c]\n",'a');
	printf("[%*c]\n",-10,'a');
	printf("[%c]\n",'a');
	printf("[%*c]\n",0,'a');
}
