/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:00:00 by mergarci          #+#    #+#             */
/*   Updated: 2025/12/02 10:00:00 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Read line from stdin (non-interactive)
*/
char	*read_line_stdin(void)
{
	char	*buf;
	int		len;

	buf = ft_gnl(STDIN_FILENO, NULL);
	if (buf)
	{
		len = ft_strlen(buf);
		if (len > 0 && buf[len - 1] == '\n')
			buf[len - 1] = '\0';
	}
	return (buf);
}

/*
** Handle readline with history
*/
char	*read_line_interactive(int type)
{
	char	*buf;

	buf = readline(prompt(type));
	if (g_status.last_signal == SIGQUIT)
		(void)0;
	else if (g_status.last_signal == SIGINT)
		(void)0;
	else if (feof(stdin))
		exit(EXIT_SUCCESS);
	if (buf && buf[0] != '\0')
		add_history(buf);
	return (buf);
}

/*
** Separate operators and update line
*/
char	*handle_operator_separation(char *line)
{
	char	*separated_line;

	separated_line = separate_operators(line);
	if (separated_line)
	{
		free(line);
		return (separated_line);
	}
	return (line);
}

/*
** Execute parsed tokens
*/
void	execute_and_update_status(t_token *tokens, t_env *env, int status)
{
	if (status == 0)
	{
		status = bash_execute(tokens, env);
		update_exit_status(status);
		main_signal_config();
	}
	else
		update_exit_status(status);
}
