/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:34:27 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:52 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/*
** Check for newline flag
*/
static bool	check_newline_flag(char *arg)
{
	int	j;

	if (ft_strncmp(arg, "-n", 2) != 0)
		return (false);
	j = 2;
	while (arg[j] == 'n')
		j++;
	if (arg[j] == '\0')
		return (true);
	return (false);
}

/*
** Echo command
*/
void	ft_echo(char **args)
{
	int		i;
	bool	newline;

	if (args == NULL || args[0] == NULL)
	{
		ft_printf("\n");
		return ;
	}
	i = 1;
	newline = TRUE;
	while (args[i] != NULL && check_newline_flag(args[i]))
	{
		newline = FALSE;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
}
