/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strncmp.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/21 17:30:29 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/21 11:51:38 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Functions lexicographically compare the null-terminated strings s1 and s2.*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (uc_s1[i] != '\0' && uc_s2[i] != '\0' && i < n)
	{
		if ((uc_s1[i] != uc_s2[i]))
			return (uc_s1[i] - uc_s2[i]);
		i++;
	}
	if (i == n)
		i--;
	return (uc_s1[i] - uc_s2[i]);
}

/*int	main(void)
{
	char	*str1 = "1234";
	char 	*str2 = "1235";
	int n;

	n = 53;
	printf("La cadena 1 es: %s\n", str1);
	printf("La cadena 2 es: %s\n", str2);
	printf("Resultado de la funcion es: %d\n", strncmp(str1,str2,n));
	printf("El resultado de mi funcion es: %d\n", ft_strncmp(str1, str2, n));
	return (0);
}
*/