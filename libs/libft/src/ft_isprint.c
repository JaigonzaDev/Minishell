#include "libft.h"

/* Function tests for a decimal digit character*/
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*
int	main(void)
{
	int	c;

	c = 32;
	printf("valor de isprint: %d\n", isprint(c));
	printf("valor de ft_isprint: %d\n", ft_isprint(c));

	return (1);
}*/