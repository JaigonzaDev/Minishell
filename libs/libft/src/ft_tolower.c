/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:33:16 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:30 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Function converts an upper-case letter to the corresponding
lower-case letter.*/
int	ft_tolower(int c)
{
	if (ft_isalpha(c) && (c >= 'A' && c <= 'Z'))
		c = c + 32;
	return (c);
}

/*int	main(void)
{
	int c = 'A';
	printf("tolower: %c pasa a %c \n", c, tolower(c));
	printf("ft_tolower: %c pasa a %c \n", c, ft_tolower(c));
}	*/
