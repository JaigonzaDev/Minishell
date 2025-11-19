/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 13:48:26 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/18 14:20:18 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Checks for white-space characters.  In the "C" and  "POSIX"  locales, 
these are: space, form-feed ('\f'), newline ('\n'), carriage return ('\r'),
horizontal tab  ('\t'),  and  vertical  tab ('\v').*/
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' \
		|| c == '\v')
		return (1);
	else
		return (0);
}
