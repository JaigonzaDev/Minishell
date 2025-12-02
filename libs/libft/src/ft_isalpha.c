#include "libft.h"

/* Alphabetic character test. Function tests for any character that
is upper or lower */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 81;
	printf("valor de isalpha: %d\n", isalpha(c));
	printf("valor de ft_isalpha: %d\n", ft_isalpha(c));

	return (1);
}*/