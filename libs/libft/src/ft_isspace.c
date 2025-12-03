/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:31:23 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:00 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Checks for white-space characters.  In the "C" and  "POSIX"  locales,
these are: space, form-feed ('\f'), newline ('\n'), carriage return ('\r'),
horizontal tab  ('\t'),  and  vertical  tab ('\v').*/
int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	else
		return (0);
}
