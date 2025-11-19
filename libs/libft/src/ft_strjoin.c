/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/24 20:58:26 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/24 20:58:26 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Reserve and return a new string, formed by the concatenation 
of 's1' and 's2'.*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ptr = (char *)ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len_s1 + 1);
	ft_strlcat(ptr, s2, len_s1 + len_s2 + 1);
	return (ptr);
}

/*int main()
{
	char *str = "a todos";
	char * dst = "12345";
	dst = ft_strjoin(str, dst);
	printf("%s_%d", dst, ft_strlen(dst));

	return 0;
}*/