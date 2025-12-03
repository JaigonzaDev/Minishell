/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:33:01 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:34 by cinaquiz         ###   ########.fr       */
/*                                                                            */
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
	char	*str1;
	char	*str2;
	int		n;

	str1 = "1234";
	str2 = "1235";
	n = 53;
	printf("La cadena 1 es: %s\n", str1);
	printf("La cadena 2 es: %s\n", str2);
	printf("Resultado de la funcion es: %d\n", strncmp(str1,str2,n));
	printf("El resultado de mi funcion es: %d\n", ft_strncmp(str1, str2, n));
	return (0);
}
*/