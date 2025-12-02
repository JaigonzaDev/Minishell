#include "libft.h"

/*Free memory allocated*/
void	*ft_memfree(void *ptr)
{
	free(ptr);
	return (NULL);
}
