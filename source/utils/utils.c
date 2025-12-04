/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:16 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/04 11:17:31 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Debug tokens
*/
void	debug(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("----\n");
		printf("Token: %s, Type: %d, Exec Group: %d, Num IO: %d, Pos: %d\n",
			tokens->token, tokens->type, tokens->exec_group.group,
			tokens->exec_group.io, tokens->position);
		printf("----\n");
		tokens = tokens->next;
	}
}

/*
** Get prompt string
*/
const char	*prompt(int type)
{
	if (type == E_PROMPT_MAIN)
		return ("minishell$ ");
	else if (type == E_PROMPT_SQUOTE)
		return ("squote> ");
	else if (type == E_PROMPT_DQUOTE)
		return ("dquote> ");
	else if (type == E_PROMPT_BQUOTE)
		return ("bquote> ");
	return ("");
}

void	global_init(void)
{
	g_status.last_exit_status = 0;
	g_status.g_env_copy = NULL;
	g_status.env_count = 0;
	g_status.env_list = NULL;
}

void	clean_exit(int status)
{
	if (g_status.env_list)
		env_freeall(&g_status.env_list);
	env_free_simple();
	rl_clear_history();
	exit(status);
}
