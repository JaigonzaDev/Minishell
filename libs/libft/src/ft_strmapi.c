/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strmapi.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/26 17:53:04 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/26 17:53:04 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* To each character of the string 's', apply the function 'f' giving as 
parameters the index of each character within 's' and the character itself.
Generates a new string with the result of successive use of 'f' */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str || f == NULL)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
/*
char	ft_MGM(unsigned int i, char c)
{
	(void)i;
	if ((c >= 'A' && c <= 'Z') )
		return (ft_tolower(c));
	return (ft_toupper(c));
}

int main(void)
{
	char *str = "HolA aAaA tOdOOooSSSsss";
	printf("Original: \"%s\"\n", str);
	printf("Aplicando ft_MGM: \"%s\"\n", ft_strmapi(str, ft_MGM));
	return 1;
}*/