/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:28:21 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:29:55 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handle expect command state
*/
int	handle_expect_cmd(t_token *current, int *state)
{
	if (is_word(current->type))
		*state = E_STATE_EXPECT_ARG;
	else if (is_redirection(*current))
		*state = E_STATE_EXPECT_FILENAME;
	else if (current->type == E_PIPE)
		return (syntax_error(current->token, E_ERROR_UNEXPECTED));
	return (0);
}

/*
** Handle expect arg state
*/
int	handle_expect_arg(t_token *current, int *state)
{
	if (is_word(current->type))
		*state = E_STATE_EXPECT_ARG;
	else if (is_redirection(*current))
	{
		if (current->type == E_REDIRECT_HEREDOC)
			*state = E_STATE_EXPECT_DELIMITER;
		else
			*state = E_STATE_EXPECT_FILENAME;
	}
	else if (current->type == E_PIPE)
		*state = E_STATE_EXPECT_CMD;
	return (0);
}

/*
** Handle expect filename state
*/
int	handle_expect_filename(t_token *current, int *state)
{
	if (current->type == E_FILE)
	{
		if (current->exec_group.io == E_STDIN && open(current->token,
				O_RDONLY) == -1)
			return (syntax_error(current->token, E_ERROR_MISSING_FILE));
		*state = E_STATE_EXPECT_ARG;
	}
	else if (is_word(current->type) || current->type == 0)
		*state = E_STATE_EXPECT_ARG;
	else if (is_operator(*current))
		return (syntax_error(current->token, E_ERROR_UNEXPECTED));
	else if (current->type == E_PIPE)
		*state = E_STATE_EXPECT_CMD;
	return (0);
}

/*
** Handle expect delimiter state
*/
int	handle_expect_delimiter(t_token *current, int *state)
{
	if (is_word(current->type))
		*state = E_STATE_EXPECT_FILENAME;
	return (0);
}
