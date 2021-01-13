#include <unistd.h>

void putnbr_recursion(int n)
{
	char c;
	char *base = "0123456789";

	if (n >= 10)
	{
		putnbr_recursion(n/10);
	}
	c = base[n % 10];
	write(1, &c, sizeof(char));
}

int main(void)
{
	putnbr_recursion(12356);
	return 0;
}
