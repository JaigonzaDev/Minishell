/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:14:28 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/04 18:38:46 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Count arguments
*/
static int	ft_count_arg(char *str)
{
	int		cont;
	bool	quote_found;
	int		i;

	i = 0;
	quote_found = false;
	cont = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (str[i] == '\'' && !quote_found)
			quote_found = true;
		else if (str[i] == '\'' && quote_found)
			quote_found = false;
		if (str[i] == ' ' && (str[i - 1] != ' ') && !quote_found)
			cont++;
		i++;
	}
	if (str[i] == '\0' && str[i - 1] == ' ')
		cont--;
	return (cont);
}

/*
** Save word
*/
static char	*ft_save_word(int len, int init, char **str)
{
	char	*str_aux;

	str_aux = (char *)ft_calloc(len + 1, sizeof(char));
	while (init--)
		(*str)++;
	while (++init < len)
		str_aux[init] = (*str)[init];
	str_aux[init] = '\0';
	return (str_aux);
}

/*
** Update quote status
*/
static void	update_quote_status(char c, bool *quote_found)
{
	if (c == '\'' && !*quote_found)
		*quote_found = true;
	else if (c == '\'' && *quote_found)
		*quote_found = false;
}

/*
** Get next word
*/
static char	*ft_get_word(char **str)
{
	int		end;
	bool	quote_found;
	int		init;

	quote_found = false;
	init = 0;
	end = 0;
	while (((*str)[end] == ' ') || ((*str)[end] == '\t'))
		(*str)++;
	while ((*str)[end])
	{
		if (((*str)[end]) == '\'')
		{
			if (!quote_found)
				init = end + 1;
			update_quote_status((*str)[end], &quote_found);
			if (quote_found == false)
				break ;
		}
		if (((*str)[end]) == ' ' && !quote_found)
			break ;
		end++;
	}
	return (ft_save_word(end - init, init, str));
}

/*
** Split string for bash
*/
char	**ft_split_bash(char *str)
{
	char	**result;
	int		n;
	int		i;

	i = -1;
	n = ft_count_arg(str);
	result = (char **)ft_calloc(n + 1, sizeof(char *));
	if (result == NULL)
		return (NULL);
	while (++i < n)
	{
		result[i] = ft_get_word(&str);
		str += ft_strlen(result[i]) + 1;
	}
	result[i] = NULL;
	return (result);
}
