#include "libft.h"

/* Allocate memory. The ft_calloc() function contiguously allocates enough
space for count objects that are size bytes of memory each and returns a
pointer to he allocated memory.  The allocated memory is filled with bytes
of value zero.*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/*int main(void)
{
	int		count = 1;
	int		n = 8;
	char	*pt = calloc(count, sizeof(int));
	char	*ptr = ft_calloc(count, sizeof(int));
	int		i = 0;

	while (i++ < n*count)
		printf("%d: %d %d\n", i, pt[i], ptr[i]);
	return (0);
}*/
