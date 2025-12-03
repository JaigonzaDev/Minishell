/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:54 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:27:20 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Process token content
*/
static int	process_token_content(char **line, t_token *token, t_env *env)
{
	while (**line != ' ' && **line != '\t' && **line != '\0')
	{
		if (quoting(line, &token, env) == 0)
		{
			if (ft_putchar(**line, &token->token) == -1)
				return (-1);
		}
		(*line)++;
	}
	return (0);
}

/*
** Main split function
*/
t_token	*bash_split(char **line, t_env *env)
{
	t_token	*tokens;
	t_token	*head;
	int		i;

	tokens = init_split(&head, &i);
	if (!tokens)
		return (NULL);
	while (**line)
	{
		tokens->position = i;
		skip_spaces(line);
		if (process_token_content(line, tokens, env) == -1)
		{
			free_token_list(head);
			return (NULL);
		}
		if (**line != '\0')
		{
			if (!handle_next_node(&tokens, head))
				return (NULL);
		}
		i++;
	}
	return (head);
}
