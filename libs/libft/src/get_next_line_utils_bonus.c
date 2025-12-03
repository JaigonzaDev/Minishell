/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:33:23 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:28 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr_gnl(char const *s, unsigned int star, size_t len)
{
	char			*ptr;
	unsigned int	len_src;

	if (!s)
		return (NULL);
	len_src = (unsigned int)ft_strlen(s);
	if (len > len_src)
		len = len_src - star;
	if (len_src < star || len_src == 0)
		return (ft_strdup(""));
	if (star + len == len_src + 1)
		len--;
	ptr = (char *)ft_calloc_gnl(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	if ((star < len || (star + len) <= len_src + 1))
	{
		while (star--)
			s++;
		ft_strlcpy(ptr, s, len + 1);
		return (ptr);
	}
	return (ptr);
}

bool	ft_strchr_gnl(char **s, char **dst, int c)
{
	char	*ptr_aux;
	int		cont;

	ptr_aux = *s;
	cont = 0;
	while (ptr_aux[cont] != '\0' && ptr_aux[cont] != (unsigned char)c)
		cont++;
	if (*dst != NULL)
		*dst = ft_memfree(*dst);
	if (ptr_aux[cont] == '\0')
	{
		*dst = NULL;
		return (false);
	}
	else
	{
		*s = ft_substr_gnl(*s, 0, ++cont);
		*dst = ft_strdup(&ptr_aux[cont]);
		ptr_aux = ft_memfree(ptr_aux);
	}
	return (true);
}
