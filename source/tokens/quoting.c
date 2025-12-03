/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:45 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:27:23 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handle single quote content
*/
void	case_squote(char **line, t_token **token)
{
	(*line)++;
	(*token)->lit = 1;
	if (**line == '$' && ft_strnstr(*line, "\"", ft_strlen(*line)) != NULL)
	{
		ft_putchar('\'', &(*token)->token);
		return ;
	}
	if (ft_strnstr(*line, "\'", ft_strlen(*line)) != NULL)
	{
		while (**line != '\'')
		{
			if (ft_putchar(**line, &(*token)->token) == -1)
				return ;
			(*line)++;
		}
	}
	else
		ft_putchar('\'', &(*token)->token);
}

/*
** Handle double quote content
*/
void	case_dquote(char **line, t_token **token, t_env *env)
{
	(*line)++;
	(*token)->lit = 1;
	if (ft_strnstr(*line, "\"", ft_strlen(*line)) != NULL)
	{
		while (**line != '\"')
		{
			if (**line == '$')
				case_dollar(line, token, env);
			else
				ft_putchar(**line, &(*token)->token);
			(*line)++;
		}
	}
	else
		ft_putchar('\"', &(*token)->token);
}

/*
** Main quoting handler
*/
int	quoting(char **line, t_token **token, t_env *env)
{
	if (**line == '\'')
	{
		case_squote(line, token);
		return (TRUE);
	}
	else if (**line == '\"')
	{
		case_dquote(line, token, env);
		return (TRUE);
	}
	else if (**line == '$')
	{
		case_dollar(line, token, env);
		return (TRUE);
	}
	else
		return (FALSE);
}
