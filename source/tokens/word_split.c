/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:27:00 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:27:16 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Split token logic
*/
static t_token	*split_logic(t_token *token, char *str)
{
	t_split_context	ctx;

	ctx.first = NULL;
	ctx.prev = NULL;
	ctx.in_word = 0;
	ctx.start = str;
	while (*str)
	{
		process_split_char(str, &ctx, token);
		str++;
	}
	if (ctx.in_word)
		link_new_token(create_split_token(ctx.start, str - ctx.start, token),
			&ctx.first, &ctx.prev);
	return (ctx.first);
}

/*
** Split token by spaces
*/
t_token	*split_token_by_spaces(t_token *token)
{
	t_token	*first_new;

	if (!token || !token->token)
		return (token);
	first_new = split_logic(token, token->token);
	if (!first_new)
	{
		if (token->prev)
			token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
		free(token->token);
		free(token);
		return (NULL);
	}
	link_split_tokens(token, first_new);
	free(token->token);
	free(token);
	return (first_new);
}

/*
** Apply word splitting
*/
t_token	*apply_word_splitting(t_token *tokens)
{
	t_token	*current;
	t_token	*next;
	t_token	*new_head;

	if (!tokens)
		return (NULL);
	current = tokens;
	new_head = tokens;
	while (current)
	{
		next = current->next;
		if (current->lit == 0 && current->token)
		{
			if (token_needs_splitting(current->token))
			{
				new_head = handle_token_split(current, new_head, next);
				current = next;
				continue ;
			}
		}
		current = next;
	}
	return (new_head);
}
