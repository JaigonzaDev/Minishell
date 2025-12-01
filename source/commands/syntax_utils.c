/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
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
** Syntax error handler
*/
int	syntax_error(char *token_value, int type)
{
	if (type == E_ERROR_UNEXPECTED)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
			token_value);
		return (2);
	}
	else if (type == E_ERROR_MISSING_FILE)
	{
		fprintf(stderr, "minishell: %s: No such File or Directory \n",
			token_value);
		return (1);
	}
	return (1);
}

/*
** Check if token is redirection
*/
int	is_redirection(t_token token)
{
	if (token.lit == 1)
		return (FALSE);
	if (token.type == E_REDIRECT_IN)
		return (TRUE);
	if (token.type == E_REDIRECT_OUT)
		return (TRUE);
	if (token.type == E_REDIRECT_APPEND)
		return (TRUE);
	if (token.type == E_REDIRECT_HEREDOC)
		return (TRUE);
	return (FALSE);
}

/*
** Check if token is operator
*/
int	is_operator(t_token token)
{
	if (token.lit == 1)
		return (FALSE);
	if (token.type == E_PIPE || is_redirection(token))
		return (1);
	return (0);
}

/*
** Check if token is word
*/
int	is_word(int type)
{
	if (type == E_ARG || type == E_COMMAND)
		return (1);
	return (0);
}
