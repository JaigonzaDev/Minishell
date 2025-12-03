/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:28:09 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:29:58 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Process commands and arguments
*/
static void	process_commands_and_args(t_token *tokens)
{
	t_token	*current;
	int		expecting_command;

	current = tokens;
	expecting_command = 1;
	while (current)
	{
		if (current->type == 0)
		{
			if (expecting_command)
			{
				current->type = E_COMMAND;
				expecting_command = 0;
			}
			else
				current->type = E_ARG;
		}
		if (current->type == E_PIPE)
			expecting_command = 1;
		current = current->next;
	}
}

/*
** Get token type name
*/
static const char	*get_token_type_name(int type)
{
	if (type == E_COMMAND)
		return ("COMMAND");
	if (type == E_ARG)
		return ("ARG");
	if (type == E_FILE)
		return ("FILE");
	if (type == E_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	if (type == E_REDIRECT_IN)
		return ("REDIRECT_IN");
	if (type == E_REDIRECT_APPEND)
		return ("REDIRECT_APPEND");
	if (type == E_REDIRECT_HEREDOC)
		return ("REDIRECT_HEREDOC");
	if (type == E_PIPE)
		return ("PIPE");
	return ("UNKNOWN");
}

/*
** Print token debug info
*/
static void	print_token_debug(t_token *current)
{
	printf("Token: '%s' | Type: %s | ", current->token,
		get_token_type_name(current->type));
	printf("Group: %d | IO: %d | Pos: %d\n", current->exec_group.group,
		current->exec_group.io, current->position);
}

/*
** Debug parsing
*/
void	debug_parsing(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		print_token_debug(current);
		current = current->next;
	}
}

/*
** Main parsing function
*/
int	parse_commands_new(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (1);
	process_pipes(*tokens);
	process_redirections(*tokens);
	process_commands_and_args(*tokens);
	return (correct_syntax(*tokens));
}
