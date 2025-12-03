/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:31:12 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:02 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Test for any ASCII character */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 222;
	printf("valor de isascii: %d\n", isascii(c));
	printf("valor de ft_isascii: %d\n", ft_isascii(c));

	return (1);
}*/