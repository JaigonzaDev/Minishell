/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_substr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/24 19:43:11 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/24 19:43:11 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Reserve and return a substring of the string 's'.
The substring starts from index 'start' and has a maximum length 'len'.*/
char	*ft_substr(char const *s, unsigned int star, size_t len)
{
	char		*ptr;
	size_t		len_src;

	if (!s)
		return (NULL);
	len_src = ft_strlen(s);
	if (len > len_src)
		len = len_src - (size_t)star;
	if (len_src < (size_t)star || len_src == 0)
		return (ft_strdup(""));
	if ((size_t)star + len == len_src + 1)
		len--;
	ptr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if (((size_t)star < len || ((size_t)star + len) <= len_src + 1))
	{
		while (star--)
			s++;
		ft_strlcpy(ptr, s, len + 1);
		return (ptr);
	}
	return (ptr);
}

/*int main()
{
	char *str = "0123456789";
	char * dst;
	dst = ft_substr(str, 9 , 10);
	printf("str: %p, %s %lu\n", str, str, ft_strlen(str));
	printf("dst: %p, %s %lu\n", dst, dst, ft_strlen(dst));
	free(dst);

	return 0;
}*/