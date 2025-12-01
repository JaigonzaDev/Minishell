/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:32:11 by mergarci          #+#    #+#             */
/*   Updated: 2025/12/01 18:43:51 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Append char to string
*/
int	ft_putchar(char c, char **s)
{
	char	*new_str;
	size_t	len;

	if (*s == NULL)
	{
		new_str = malloc(2 * sizeof(char));
		if (!new_str)
			return (-1);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	else
	{
		len = ft_strlen(*s);
		new_str = malloc((len + 2) * sizeof(char));
		if (!new_str)
			return (-1);
		ft_strlcpy(new_str, *s, len + 1);
		new_str[len] = c;
		new_str[len + 1] = '\0';
		free(*s);
	}
	*s = new_str;
	return (0);
}

/*
** Append string to buffer
*/
int	ft_putstr(char *s, char **buf)
{
	while (*s)
	{
		if (ft_putchar(*s, buf) == -1)
			return (-1);
		s++;
	}
	return (0);
}

/*
** Free token list
*/
void	free_token_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
}

/*
** Handle literal string check
*/
int	handle_literal_str(char *str, char last)
{
	if (last == '\"' && ft_strnstr(str, "\"", ft_strlen(str)) != NULL)
		return (1);
	if (last == '\'' && ft_strnstr(str, "\'", ft_strlen(str)) != NULL)
		return (1);
	return (0);
}
