/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42madrid.com> +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/01 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Skip spaces
*/
void	skip_spaces(char **line)
{
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

/*
** Process split char
*/
void	process_split_char(char *str, t_split_context *ctx, t_token *token)
{
	if (*str == ' ' || *str == '\t')
	{
		if (ctx->in_word)
		{
			link_new_token(create_split_token(ctx->start, str - ctx->start,
					token), &ctx->first, &ctx->prev);
			ctx->in_word = 0;
		}
	}
	else if (!ctx->in_word)
	{
		ctx->start = str;
		ctx->in_word = 1;
	}
}

/*
** Check if token needs splitting
*/
int	token_needs_splitting(char *str)
{
	while (*str && *str != ' ' && *str != '\t')
		str++;
	return (*str != '\0');
}

/*
** Handle token split
*/
t_token	*handle_token_split(t_token *current, t_token *new_head, t_token *next)
{
	t_token	*first_split;

	first_split = split_token_by_spaces(current);
	if (!first_split && current == new_head)
		return (next);
	else if (first_split && current == new_head)
		return (first_split);
	return (new_head);
}

/*
** Initialize split
*/
t_token	*init_split(t_token **head, int *i)
{
	t_token	*tokens;

	tokens = create_new_token_node(NULL);
	*head = tokens;
	*i = 0;
	return (tokens);
}
