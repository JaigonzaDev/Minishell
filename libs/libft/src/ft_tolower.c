#include "libft.h"

/* Function converts an upper-case letter to the corresponding
lower-case letter.*/
int	ft_tolower(int c)
{
	if (ft_isalpha(c) && (c >= 'A' && c <= 'Z'))
		c = c + 32;
	return (c);
}

/*int	main(void)
{
	int c = 'A';
	printf("tolower: %c pasa a %c \n", c, tolower(c));
	printf("ft_tolower: %c pasa a %c \n", c, ft_tolower(c));
}	*/
