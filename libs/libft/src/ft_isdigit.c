#include "libft.h"

/* Function tests for a decimal digit character */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 47;
	printf("valor de isdigit: %d\n", isdigit(c));
	printf("valor de ft_isdigit: %d\n", ft_isdigit(c));

	return (1);
}*/