/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strdup.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/22 17:27:49 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/22 18:06:10 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Function allocates sufficient memory for a copy of the string s1, does 
the copy, and returns a pointer to it. */
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (ptr == NULL || !s1)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
int main(void)
{
	char *ptr = "holi!!";
	printf("ptr: %s\n", ptr);
	char *b = ft_strdup(ptr);
	printf("b: %s\n", b);
	return 1;
}*/