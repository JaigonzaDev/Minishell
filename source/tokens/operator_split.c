/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:55:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/12/01 18:43:09 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if char is shell operator
*/
static int	is_shell_operator(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

/*
** Check if string is compound operator
*/
static int	is_compound_operator(char *str)
{
	if (!str || !str[0] || !str[1])
		return (0);
	return ((str[0] == '>' && str[1] == '>') || (str[0] == '<'
			&& str[1] == '<'));
}

/*
** Update quote state
*/
static void	update_quote_state(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !*in_dquote)
		*in_squote = !*in_squote;
	else if (c == '\"' && !*in_squote)
		*in_dquote = !*in_dquote;
}

/*
** Process operator separation
*/
static void	process_separation(char *input, char *result, int *i, int *j)
{
	if (is_compound_operator(&input[*i]))
	{
		if (*j > 0 && result[*j - 1] != ' ')
			result[(*j)++] = ' ';
		result[(*j)++] = input[(*i)++];
		result[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] != ' ' && input[*i] != '\t')
			result[(*j)++] = ' ';
	}
	else if (is_shell_operator(input[*i]))
	{
		if (*j > 0 && result[*j - 1] != ' ')
			result[(*j)++] = ' ';
		result[(*j)++] = input[(*i)++];
		if (input[*i] && input[*i] != ' ' && input[*i] != '\t')
			result[(*j)++] = ' ';
	}
}

/*
** Separate operators
*/
char	*separate_operators(char *input)
{
	char	*result;
	int		i;
	int		j;
	int		in_squote;
	int		in_dquote;

	if (!input)
		return (NULL);
	result = (char *)ft_calloc(ft_strlen(input) * 2 + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_squote = 0;
	in_dquote = 0;
	while (input[i])
	{
		update_quote_state(input[i], &in_squote, &in_dquote);
		if (!in_squote && !in_dquote && (is_compound_operator(&input[i])
				|| is_shell_operator(input[i])))
			process_separation(input, result, &i, &j);
		else
			result[j++] = input[i++];
	}
	return (result);
}
