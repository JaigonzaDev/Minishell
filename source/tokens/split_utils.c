/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:51 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:27:21 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Create new token node
*/
t_token	*create_new_token_node(t_token *prev)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_token));
	new_node->prev = prev;
	return (new_node);
}

/*
** Create split token
*/
t_token	*create_split_token(char *start, int len, t_token *orig)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	ft_memset(new_token, 0, sizeof(t_token));
	new_token->token = ft_substr(start, 0, len);
	new_token->type = orig->type;
	new_token->position = orig->position;
	new_token->lit = 0;
	return (new_token);
}

/*
** Link new token
*/
void	link_new_token(t_token *new, t_token **first, t_token **prev)
{
	if (!*first)
		*first = new;
	if (*prev)
		(*prev)->next = new;
	new->prev = *prev;
	*prev = new;
}

/*
** Link split tokens
*/
void	link_split_tokens(t_token *token, t_token *first_new)
{
	t_token	*last_new;

	if (token->next)
	{
		last_new = first_new;
		while (last_new->next)
			last_new = last_new->next;
		last_new->next = token->next;
		token->next->prev = last_new;
	}
	if (token->prev)
	{
		token->prev->next = first_new;
		first_new->prev = token->prev;
	}
}

/*
** Handle next node creation for bash_split
*/
int	handle_next_node(t_token **tokens, t_token *head)
{
	(*tokens)->next = create_new_token_node(*tokens);
	if (!(*tokens)->next)
	{
		free_token_list(head);
		return (0);
	}
	*tokens = (*tokens)->next;
	return (1);
}
