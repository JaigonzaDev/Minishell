/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:31:02 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:04 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft.h"
#include <stdio.h>

/*Counts the non-null pointers in a NULL-terminated array of pointers
(returning 0 if the array itself is NULL).
BE CAREFUL!! You will have to cast the pointer:
ft_count_elem((const void * const*)argv)*/
int	ft_count_elem(const void *const *ptr)
{
	int	len;

	len = 0;
	if (ptr)
	{
		while (ptr[len])
			len++;
	}
	return (len);
}

/*Counts the non-null pointers in a NULL-terminated array of pointers
(returning 0 if the array itself is NULL).
BE CAREFUL!! You will have to cast the pointer:
ft_count_elem((const void * const*)argv)*/
int	ft_count_strs(char **ptr)
{
	int	len;

	len = 0;
	if (ptr)
	{
		while (ptr[len])
			len++;
	}
	return (len);
}

/*int main(int argc, char *argv[])
{
	(void)argv;
	printf("%d, %d\n", argc, ft_count_elem((const void * const*)argv));
	return (0);
}*/
