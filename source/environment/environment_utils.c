/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/12/02 00:00:00 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Allocate variable content
*/
void	allocate_var_content(t_env *var, char *str, char *equal_pos)
{
	int	var_len;

	var_len = equal_pos - str;
	var->var = malloc(var_len + 1);
	if (!var->var)
	{
		var->var = ft_strdup("");
		var->content = ft_strdup("");
		return ;
	}
	ft_strlcpy(var->var, str, var_len + 1);
	var->content = ft_strdup(equal_pos + 1);
	if (!var->content)
		var->content = ft_strdup("");
}
