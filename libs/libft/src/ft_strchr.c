/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/20 16:03:46 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/20 19:24:53 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function locates the first occurrence of c in the string pointed to by s*/
char	*ft_strchr(const char *s, int c)
{
	int				found_char;
	unsigned char	c_aux;

	c_aux = c;
	found_char = 0;
	while (*s != '\0')
	{
		if (*s == c_aux)
		{
			found_char = 1;
			break ;
		}
		else
			s++;
	}
	if (!found_char && c_aux != '\0')
		return (NULL);
	return ((char *)s);
}

/*int	main(void)
{
	char	str1[100] = "the cake is a lie\0 holaaa!";
	char	str2[100] = "the cake is a lie\0 holaaa!";
	int c = 'e' + 256;
	char *fun = strchr(str1, c);
	char *my = ft_strchr(str2, c);
	
	printf("Cadena: %s\n", str1);
	printf("Resultado de la funcion es: %s\n", fun);
	printf("Resultado de mi funcion es: %s\n", my);
	printf("comparacion funciones: %d\n", strcmp(fun, my));
	
	return (0);
}*/
