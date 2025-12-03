/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:41 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:03 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Count pipes
*/
int	count_pipes(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == E_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

/*
** Create new token node
*/
t_token	create_token_node(t_token *current, t_token *prev)
{
	t_token	new_node;

	new_node.token = current->token;
	new_node.type = current->type;
	new_node.exec_group = current->exec_group;
	new_node.position = current->position;
	new_node.next = NULL;
	new_node.prev = prev;
	return (new_node);
}

/*
** Get group tokens
*/
t_token	get_group_tokens(t_token *tokens, int group)
{
	t_token	head;
	t_token	*current;
	t_token	*new_current;

	head.next = NULL;
	current = tokens;
	new_current = &head;
	while (current)
	{
		if (current->exec_group.group == group && current->type != E_PIPE)
		{
			new_current->next = (t_token *)malloc(sizeof(t_token));
			*new_current->next = create_token_node(current, new_current);
			new_current = new_current->next;
		}
		current = current->next;
	}
	return (*head.next);
}
