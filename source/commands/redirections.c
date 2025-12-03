/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:28:15 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:29:57 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Identify redirection type
*/
static int	identify_redirection(char *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (E_REDIRECT_APPEND);
	else if (ft_strncmp(token, "<<", 2) == 0)
		return (E_REDIRECT_HEREDOC);
	else if (token[0] == '>' && ft_strlen(token) == 1)
		return (E_REDIRECT_OUT);
	else if (token[0] == '<' && ft_strlen(token) == 1)
		return (E_REDIRECT_IN);
	return (0);
}

/*
** Mark redirection file
*/
static void	mark_redirection_file(t_token *redirect_token, t_token *file_token,
		int redirect_type)
{
	if (!redirect_token || !file_token)
		return ;
	redirect_token->type = redirect_type;
	if (!is_operator(*file_token))
	{
		file_token->type = E_FILE;
		if ((redirect_type == E_REDIRECT_OUT)
			|| (redirect_type == E_REDIRECT_APPEND))
			file_token->exec_group.io = E_STDOUT;
		else if ((redirect_type == E_REDIRECT_IN)
			|| (redirect_type == E_REDIRECT_HEREDOC))
			file_token->exec_group.io = E_STDIN;
	}
}

/*
** Process redirections
*/
void	process_redirections(t_token *tokens)
{
	t_token	*current;
	int		redirect_type;

	current = tokens;
	while (current)
	{
		redirect_type = identify_redirection(current->token);
		if (current->type == 0)
			current->type = redirect_type;
		if (redirect_type && current->next
			&& identify_redirection(current->next->token) == 0)
		{
			if (redirect_type == E_REDIRECT_HEREDOC && current->next->next)
				mark_redirection_file(current, current->next->next,
					redirect_type);
			else
				mark_redirection_file(current, current->next, redirect_type);
			if (!is_operator(*current->next))
				current = current->next;
		}
		current = current->next;
	}
}
