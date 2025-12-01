/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:47:08 by mergarci          #+#    #+#             */
/*   Updated: 2025/08/30 18:55:37 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** Unset environment variable
*/
void	ft_unset(char *var, t_env **enviroment)
{
	t_env *current;
	t_env *prev;

	if (var == NULL || enviroment == NULL || *enviroment == NULL)
		return ;
	current = *enviroment;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(current->var, var, ft_strlen(var) + 1) == 0)
		{
			if (prev == NULL)
				*enviroment = current->next;
			else
				prev->next = current->next;
			env_free(current);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}