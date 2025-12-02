/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 20:10:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:10:00 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Join expansion parts
*/
char	*join_expansion_parts(char *before, char *status, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, status);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, after);
	free(temp);
	return (result);
}
