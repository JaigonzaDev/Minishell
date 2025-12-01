/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42madrid.com> +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/01 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/*
** Add NULL to args pointer
*/
char	**ft_add_null(char **args)
{
	char	**aux;
	int		num;
	int		i;

	num = ft_count_string(args);
	i = 0;
	aux = (char **)ft_calloc(num + 1, sizeof(char *));
	while (i < num)
	{
		aux[i] = (char *)ft_calloc(ft_strlen(args[i]) + 1, sizeof(char *));
		ft_memcpy(aux[i], args[i], ft_strlen(args[i]));
		i++;
	}
	aux[num] = NULL;
	if (num == 1)
	{
		args[0] = ft_memfree(args[0]);
		args = NULL;
	}
	return (aux);
}

/*
** Free string array
*/
void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
** Handle command not found
*/
int	handle_cmd_not_found(char **args)
{
	ft_printf("minishell: %s: command not found\n", args[0]);
	free_str_array(args);
	return (127);
}

/*
** Handle permission denied
*/
int	handle_permission_denied(char **args, char *path)
{
	ft_printf("minishell: %s: Permission denied\n", args[0]);
	free(path);
	free_str_array(args);
	return (126);
}
