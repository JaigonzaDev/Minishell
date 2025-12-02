#include "libft.h"

/* Function converts a lower-case letter to the corresponding
upper-case letter.*/
int	ft_toupper(int c)
{
	if (ft_isalpha(c) && (c >= 'a' && c <= 'z'))
		c = c - 32;
	return (c);
}

/*int	main(void)
{
	int c = 'a';
	printf("toupper: %c pasa a %c \n", c, toupper(c));
	printf("ft_toupper: %c pasa a %c \n", c, ft_toupper(c));
}	*/
