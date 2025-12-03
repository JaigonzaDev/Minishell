/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:16 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:26:27 by jaigonza         ###   ########.fr       */
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
		return ("bash-mini$ ");
	else if (type == E_PROMPT_SQUOTE)
		return ("squote> ");
	else if (type == E_PROMPT_DQUOTE)
		return ("dquote> ");
	else if (type == E_PROMPT_BQUOTE)
		return ("bquote> ");
	return ("");
}
