/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:20:45 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/18 14:24:02 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Checks the minimum number. It returns the minimum number*/
int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}
