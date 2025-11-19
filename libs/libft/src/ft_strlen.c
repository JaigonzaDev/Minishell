/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strlen.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/16 12:27:21 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/15 15:32:12 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <stdio.h>

/* Function computes the length of the string s.*/
size_t	ft_strlen(const char *s)
{
	size_t	cont;

	cont = 0;
	while (s[cont] != '\0')
		cont++;
	return (cont);
}

/*int	main(void)
{
	char 	*str = "holi";
	
	//printf("La cadena \"%s\" tiene %d caracteres\n", str, strlen(str));
	printf("La cadena \"%s\" tiene %d caracteres\n", str, ft_strlen(str));
}*/