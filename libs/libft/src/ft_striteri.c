/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_striteri.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/26 18:20:05 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/26 18:20:05 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* To each character of the string 's', apply the function 'f' giving as 
parameters the index of each character within 's' and the address of the 
character itself, which can be modified if necessary.*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s != NULL && f != NULL)
	{
		while (s[i] != '\0')
		{
			f(i, &s[i]);
			i++;
		}
	}
}

/*
int main(void)
{
	char *str = "hola a todos";
	printf("Original: \"%s\". %c\n", str, ft_toupper('c'));
	ft_striteri(str, &ft_MGM);
	printf("Aplicando ft_MGM: \"%s\"\n", str);

	return 1;
}*/