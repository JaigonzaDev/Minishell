/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:31:53 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:51 by cinaquiz         ###   ########.fr       */
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
