/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:31:06 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:04 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Alphanumeric character test. Check if ft_isalpha or isdigit is true. */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/*int	main(void)
{
	int	c;

	c = 47;
	printf("valor de isalnum: %d\n", isalnum(c));
	printf("valor de ft_isalnum: %d\n", ft_isalnum(c));

	return (1);
}*/