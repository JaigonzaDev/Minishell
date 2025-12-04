/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:57:21 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/04 14:54:25 by cinaquiz         ###   ########.fr       */
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
	if (feof(stdin))
		clean_exit(EXIT_SUCCESS);
	if (buf && buf[0] != '\0')
		add_history(buf);
	return (buf);
}
