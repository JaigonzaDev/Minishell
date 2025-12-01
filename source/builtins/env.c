/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:48:52 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/25 16:01:49 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>

/*
** Print environment variables
*/
void	ft_env(t_env *enviroment)
{
	t_env	*tmp;

	if (!enviroment)
		return ;
	tmp = enviroment;
	while (tmp != NULL)
	{
		printf("%s=%s\n", tmp->var, tmp->content);
		tmp = tmp->next;
	}
}
