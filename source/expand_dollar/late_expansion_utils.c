/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_expansion_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:27:46 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:30:02 by jaigonza         ###   ########.fr       */
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
