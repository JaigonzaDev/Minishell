/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza cinaquiz <jaigonza@student.42m    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:28:24 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/04 10:53:32 by jaigonza ci      ###   ########.fr       */
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
		printf("minishell: syntax error near unexpected token `%s'\n",
			token_value);
		return (2);
	}
	else if (type == E_ERROR_MISSING_FILE)
	{
		printf("minishell: %s: No such File or Directory \n",
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
