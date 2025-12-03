/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:22 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 09:57:59 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Separate operators and update line
*/
char	*handle_operator_separation(char *line)
{
	char	*separated_line;

	separated_line = separate_operators(line);
	if (separated_line)
	{
		free(line);
		return (separated_line);
	}
	return (line);
}

/*
** Execute parsed tokens
*/
void	execute_and_update_status(t_token *tokens, t_env *env, int status)
{
	if (status == 0)
	{
		status = bash_execute(tokens, env);
		update_exit_status(status);
		main_signal_config();
	}
	else
		update_exit_status(status);
}
