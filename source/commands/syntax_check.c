/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
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
** Check syntax
*/
/*
** Process state
*/
static int	process_state(t_token *current, int *state)
{
	if (*state == E_STATE_EXPECT_CMD)
		return (handle_expect_cmd(current, state));
	else if (*state == E_STATE_EXPECT_ARG)
		return (handle_expect_arg(current, state));
	else if (*state == E_STATE_EXPECT_FILENAME)
		return (handle_expect_filename(current, state));
	else if (*state == E_STATE_EXPECT_DELIMITER)
		return (handle_expect_delimiter(current, state));
	return (0);
}

/*
** Check syntax
*/
int	correct_syntax(t_token *tokens)
{
	t_token	*current;
	int		state;
	int		ret;

	current = tokens;
	state = E_STATE_EXPECT_CMD;
	if (current == NULL || current->token == NULL || *current->token == '\0')
		return (0);
	while (current != NULL)
	{
		ret = process_state(current, &state);
		if (ret != 0)
			return (ret);
		current = current->next;
	}
	if (state == E_STATE_EXPECT_FILENAME || state == E_STATE_EXPECT_CMD)
		return (syntax_error("newline", E_ERROR_UNEXPECTED));
	return (0);
}
