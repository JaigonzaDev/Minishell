/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:34:33 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:34:51 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "libft.h"

/*
** Check if exit code is valid
*/
static int	is_valid_exit_code(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
** Process exit arguments
*/
static void	process_exit_args(char **args, int *exit_code)
{
	long	num;

	if (!is_valid_exit_code(args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		*exit_code = 2;
	}
	else if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		*exit_code = 1;
	}
	else
	{
		num = ft_atol(args[1]);
		*exit_code = (unsigned char)(num % 256);
	}
}

/*
** Exit builtin
*/
void	ft_exit(char **args, t_env **environment)
{
	int	exit_code;

	exit_code = 0;
	if (args[1])
		process_exit_args(args, &exit_code);
	if (environment != NULL && *environment != NULL)
	{
		env_freeall(environment);
		*environment = NULL;
	}
	exit(exit_code);
}
