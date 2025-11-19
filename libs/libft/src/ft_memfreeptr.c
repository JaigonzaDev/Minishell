/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memfreeptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:02:20 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/25 17:44:12 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Frees the memory of each element of a NULL-terminated array of pointers 
and always returns NULL*/
char	**ft_memfree_ptr(void **ptr)
{
	int	n;

	n = ft_count_elem((const void *const *)ptr);
	if (n != 0)
	{
		while (--n >= 0)
			ptr[n] = ft_memfree(ptr[n]);
	}
	return (NULL);
}

/*Frees the memory of each element of a NULL-terminated array of strings 
and always returns NULL*/
char	**ft_memfree_str(char **ptr)
{
	int	n;

	n = ft_count_elem((const void *const *)ptr);
	if (n != 0)
	{
		while (--n >= 0)
			ptr[n] = ft_memfree(ptr[n]);
	}
	free(ptr);
	return (NULL);
}
/*int main(int argc, char *argv[])
{
	char **cpy;

	(void)argc;
	(void)argv;
	cpy = ft_split("hola a todos", ' ');
	printf("%p,%s\n", *cpy, (char *)cpy[0] );
	ft_memfreeptr((void **)cpy);
	printf("%p,\n", *cpy );
	return (0);
}*/
