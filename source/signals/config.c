/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:27:09 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/04 11:17:29 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parent signal handler
*/
void	parent_handler(int signum)
{
	(void)signum;
	g_status.last_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
** Child signal handler
*/
void	child_handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

/*
** Quit signal handler
*/
void	quit_handler(int signum)
{
	(void)signum;
	if (rl_line_buffer && ft_strlen(rl_line_buffer) > 0)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		clean_exit(131);
	}
}

/*
** Main signal configuration
*/
void	main_signal_config(void)
{
	struct sigaction	sa;

	rl_catch_signals = 0;
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = parent_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = quit_handler;
	sigaction(SIGQUIT, &sa, NULL);
}

/*
** Child signal configuration
*/
void	child_signal_config(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
