/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:28:12 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:29:57 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Mark pipes
*/
static void	mark_pipes(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->token && current->token[0] == '|'
			&& ft_strlen(current->token) == 1)
		{
			current->type = E_PIPE;
		}
		current = current->next;
	}
}

/*
** Assign groups based on pipes
*/
static void	assign_groups(t_token *tokens)
{
	t_token	*current;
	int		group;

	current = tokens;
	group = 0;
	while (current)
	{
		current->exec_group.group = group;
		if (current->type == E_PIPE)
			group++;
		current = current->next;
	}
}

/*
** Process pipes
*/
void	process_pipes(t_token *tokens)
{
	mark_pipes(tokens);
	assign_groups(tokens);
}
