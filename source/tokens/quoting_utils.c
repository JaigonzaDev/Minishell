/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:37 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 09:34:21 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handle environment variable expansion
*/
static void	handle_env_var(char **line, t_token **token, t_env *env)
{
	char	*var;
	char	*value;

	var = NULL;
	while (*(*line + 1) != ' ' && *(*line + 1) != '\t' && *(*line + 1) != '\0'
		&& *(*line + 1) != '\'' && *(*line + 1) != '$')
	{
		if (((*token)->lit == 1 && *(*line + 1) == '\"'))
			break ;
		ft_putchar(**line, &var);
		(*line)++;
	}
	ft_putchar(**line, &var);
	if (var == NULL)
	{
		ft_putchar('$', &(*token)->token);
		return ;
	}
	value = search_env_var(var, env);
	if (value != NULL)
		ft_putstr(value, &(*token)->token);
	free(var);
}

/*
** Handle special variables ($?, $0, etc)
*/
static int	handle_special_vars(char **line, t_token **token)
{
	if (**line == '?')
	{
		if (ft_putstr(ft_itoa(g_status.last_exit_status), &(*token)->token)
			== -1)
			return (1);
		return (1);
	}
	if (**line >= '0' && **line <= '9')
	{
		if (**line == '0')
		{
			if (ft_putstr("minishell", &(*token)->token) == -1)
				return (1);
		}
		return (1);
	}
	return (0);
}

/*
** Handle dollar expansion
*/
void	case_dollar(char **line, t_token **token, t_env *env)
{
	if (*(*line + 1) == '\"')
	{
		ft_putchar('$', &(*token)->token);
		return ;
	}
	(*line)++;
	if (**line == '\'')
	{
		ft_putchar('$', &(*token)->token);
		ft_putchar(**line, &(*token)->token);
		return ;
	}
	if (handle_special_vars(line, token))
		return ;
	handle_env_var(line, token, env);
}
