/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:34:30 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:52 by cinaquiz         ###   ########.fr       */
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
