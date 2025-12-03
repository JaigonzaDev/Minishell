/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:37:07 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:38:11 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Count valid tokens for args
*/
int	count_valid_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if ((current->type == E_COMMAND || current->type == E_ARG)
			&& current->token != NULL && current->token[0] != '\0')
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}

/*
** Convert tokens to args array
*/
char	**tokens_to_args(t_token *tokens)
{
	char	**args;
	int		count;
	int		i;
	t_token	*current;

	if (!tokens)
		return (NULL);
	count = count_valid_tokens(tokens);
	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	current = tokens;
	while (current)
	{
		if ((current->type == E_COMMAND || current->type == E_ARG)
			&& current->token != NULL && current->token[0] != '\0')
		{
			args[i++] = ft_strdup(current->token);
		}
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

/*
** Free args array
*/
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
