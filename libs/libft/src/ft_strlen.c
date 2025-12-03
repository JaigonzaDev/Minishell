/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:32:55 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:34 by cinaquiz         ###   ########.fr       */
/*                                                                            */
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