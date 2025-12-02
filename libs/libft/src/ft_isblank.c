#include "libft.h"

/*Checks for a blank character; that is, a space or a tab.*/
int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}
