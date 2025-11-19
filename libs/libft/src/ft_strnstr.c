/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strnstr.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/22 11:54:01 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/22 13:33:00 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Locate a substring in a string */
char	*ft_strnstr(const char *src, const char *need, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = (char *)src;
	if (*need == '\0')
		return (ptr);
	while (src[i] != '\0' && i < len)
	{
		if (src[i] == need[0])
		{
			while (src[i + j] == need[j] && need[j] != '\0' && i + j < len)
				j++;
			if (need[j] == '\0' && j <= len)
				return (&ptr[i]);
			j = 0;
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char *largestring = "12335456789";
	char *smallstring = "12335456789";
	char *fun;
	char *my;
	size_t n = ft_strlen(largestring);
	
	fun = strnstr(largestring, smallstring, n);
	my = ft_strnstr(largestring, smallstring, n);
	printf("Resultado strnstr: %s\n", fun);
	printf("Resultado ft_strnstr: %s\n", my);
	printf("comparacion funciones: %d\n", strcmp(fun, my));
	return (0);
}*/