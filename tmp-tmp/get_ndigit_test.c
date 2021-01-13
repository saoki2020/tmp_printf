#include <stdio.h>

int			ft_get_ndigit(long long n)
{
	int					i;
	unsigned long long	n_u;

	i = 0;
	if (n == 0)
	{
		n_u = 0;
		i = 1;
	}
	else if (n < 0)
		n_u = -n;
	else
		n_u = n;
	while (n_u > 0)
	{
		i++;
		n_u /= 10;
	}
	return (i);
}

int main(void)
{
	int i;

	i = ft_get_ndigit(100);
	printf("%d\n",i);

}
