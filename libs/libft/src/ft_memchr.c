/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_memchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/21 11:53:57 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/21 14:57:09 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function locates the first occurrence of c (converted to an unsigned char)
in string s. */
void	*ft_memchr(const void *s, int c, size_t n)
{
	int		found_char;
	char	c_aux;
	size_t	i;
	char	*src;

	c_aux = (char)c;
	found_char = 0;
	src = (char *)s;
	i = 0;
	while (s++ != NULL && i++ < n)
	{
		if (*src == c_aux)
		{
			found_char = 1;
			break ;
		}
		src++;
	}
	if (c_aux == '\0' && *src == c_aux)
		found_char = 1;
	if (!found_char || n == 0)
		return (NULL);
	return ((void *)src);
}

/*int	main(void)
{
	//char	str1[100] = "the ca\6ke is a lie\0 holaaa!";
	//char	str2[100] = "the ca\6ke is a lie\0 holaaa!";
	char str1[] = {0, 1, 2 ,3 ,4 ,5};
	char str2[] = {0, 1, 2 ,3 ,4 ,5};
	int c = 2;
	size_t n = 3;
	char *fun = memchr(str1, c, n);
	char *my = ft_memchr(str2, c, n);
	
	printf("Cadena: %p\n", str1);
	printf("Antes de funciones: str1: %p str2: %p\n", str1, str2);

	printf("Resultado de la funcion es: %p\n", fun);
	printf("Resultado de mi funcion es: %p\n", my);
	printf("Despues de funciones: str1: %p str2: %p\n", fun, my);

	printf("comparacion funciones: %d\n", strcmp(fun, my));

	return (0);
}*/