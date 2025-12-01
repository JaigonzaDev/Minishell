/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   late_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:30:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:06:53 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Join expansion parts
*/
static char	*join_expansion_parts(char *before, char *status, char *after)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(before, status);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, after);
	free(temp);
	return (result);
}

/*
** Perform single expansion
*/
static char	*perform_single_expansion(char *str, char *pos)
{
	char	*exit_status_str;
	char	*before;
	char	*after;
	char	*result;

	exit_status_str = get_exit_status_string();
	if (!exit_status_str)
		return (ft_strdup(str));
	before = ft_substr(str, 0, pos - str);
	after = ft_strdup(pos + 2);
	if (!before || !after)
	{
		free(before);
		free(after);
		free(exit_status_str);
		return (ft_strdup(str));
	}
	result = join_expansion_parts(before, exit_status_str, after);
	free(before);
	free(after);
	free(exit_status_str);
	return (result);
}

/*
** Expand exit status in string
*/
char	*expand_exit_status_in_string(char *str)
{
	char	*result;
	char	*pos;
	char	*final_result;

	if (!str)
		return (NULL);
	if (ft_strncmp(str, "$?", 3) == 0 && ft_strlen(str) == 2)
		return (get_exit_status_string());
	pos = ft_strnstr(str, "$?", ft_strlen(str));
	if (!pos)
		return (ft_strdup(str));
	result = perform_single_expansion(str, pos);
	if (!result)
		return (ft_strdup(str));
	if (ft_strnstr(result, "$?", ft_strlen(result)))
	{
		final_result = expand_exit_status_in_string(result);
		free(result);
		return (final_result);
	}
	return (result);
}

/*
** Free args on error
*/
static void	free_args_on_error(char **result, int count)
{
	int	i;

	i = count;
	while (--i >= 0)
		free(result[i]);
	free(result);
}

/*
** Count arguments
*/
static int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

/*
** Expand exit status in args
*/
char	**expand_exit_status_in_args(char **args)
{
	char	**result;
	int		i;
	int		count;

	if (!args)
		return (NULL);
	count = count_args(args);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < count)
	{
		result[i] = expand_exit_status_in_string(args[i]);
		if (!result[i])
		{
			free_args_on_error(result, i);
			return (NULL);
		}
		i++;
	}
	result[count] = NULL;
	return (result);
}
