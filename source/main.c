/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:26:06 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/04 16:55:35 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"

t_global	g_status;

/*
** Read line from input
*/
char	*read_line(int type)
{
	char	*buf;

	buf = NULL;
	if (isatty(STDIN_FILENO))
		buf = read_line_interactive(type);
	else
		buf = read_line_stdin();
	return (buf);
}

/*
** Execute bash command
*/
int	bash_execute(t_token *tokens, t_env *env)
{
	int	status;

	if (!tokens)
		return (1);
	status = execute_pipeline(tokens, env);
	return (status);
}

/*
** Process line input
*/
static void	process_line(char *line, t_env *env)
{
	t_token	*tokens;
	int		status;
	char	*line_copy;

	if (line[0] == '#')
	{
		free(line);
		return ;
	}
	line = handle_operator_separation(line);
	line_copy = line;
	tokens = bash_split(&line, env);
	free(line_copy);
	tokens = apply_word_splitting(tokens);
	status = parse_commands_new(&tokens);
	execute_and_update_status(tokens, env, status);
	free_token_list(tokens);
}

/*
** Main function
*/
int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = NULL;
	main_signal_config();
	global_init();
	env_save(envp, &env);
	while (1)
	{
		line = read_line(E_PROMPT_MAIN);
		if (!line)
			break ;
		process_line(line, env);
	}
	clean_exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
