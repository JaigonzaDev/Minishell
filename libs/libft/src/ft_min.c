/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:32:15 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:44 by cinaquiz         ###   ########.fr       */
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
