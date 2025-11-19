/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isblank.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:04:21 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/18 14:18:59 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Checks for a blank character; that is, a space or a tab.*/
int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}
