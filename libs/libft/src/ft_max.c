/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:22:59 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/18 14:23:47 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Checks the maximum number. It returns the maximum number*/
int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}
