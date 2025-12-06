/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:17:49 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/05 06:32:31 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "get_next_line_bonus.h"
# include "minishell.h"
# include <fcntl.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1
# define I 0
# define O 1
# define MAX_PIPES 1024

typedef struct s_pipe_context
{
	int	i;
	int	pipe_count;
	int	**pipes;
}		t_pipe_context;

int		ft_pipeline(int *files, char **commands, char **envp);
int		check_exec(char *command, char **envp, int status);
void	ft_print_help(void);
int		ft_count_string(char **string);
void	ft_create_fd(int *fd);
void	ft_heredoc(int *files, char *limit);
char	**ft_split_bash(char *str);
void	ft_dup_close(int fd1, int fd2, int fd_close);
void	ft_closefd(int fd);
void	ft_parent_fd(int *fd, int *fd_saved);
void	ft_close_fds(int *fd1, int *fd2);
int		ft_openfil(char *name_file, int open_mode);
int		execute_pipeline(t_token *tokens, t_env *env);
int		setup_redirections(t_token *tokens, int *input_fd, int *output_fd);
char	**tokens_to_args(t_token *tokens);
char	*find_command_in_path(char *command, char **envp, t_env *env);
int		is_command_executable(char *path);
char	**prepare_envp(char **envp, t_env *env);

int		count_valid_tokens(t_token *tokens);
void	free_args(char **args);
int		handle_redirect_in(t_token *current, int *input_fd);
int		handle_redirect_out(t_token *current, int *output_fd);
int		handle_redirect_append(t_token *current, int *output_fd);
int		handle_redirect_heredoc(t_token *current, int *input_fd);
int		process_heredoc_loop(int fd, char *delimiter);
int		process_single_redirection(t_token *prev, t_token *current,
			int *input_fd, int *output_fd);
int		exec_builtin_with_redir(char **args, t_env *env, int input_fd,
			int output_fd);
void	exec_external_child(char **args, t_env *env, int input_fd,
			int output_fd);
int		wait_external_command(pid_t pid);
int		execute_simple_command(t_token *tokens, t_env *env);
int		count_pipes(t_token *tokens);
t_token	create_token_node(t_token *current, t_token *prev);
t_token	get_group_tokens(t_token *tokens, int group);
int		execute_pipe_logic(char **args, t_env *env, int in_fd, int out_fd);
int		execute_pipe_command(t_token *tokens, t_env *env, int input_fd,
			int output_fd);
int		**create_pipes(int pipe_count);
void	close_pipes(int **pipes, int pipe_count);
void	config_child_pipes(int i, int pipe_count, int **pipes, int *fds);
void	exec_child_multi(t_pipe_context *ctx, t_token *tokens, t_env *env);
int		wait_children(pid_t *pids, int pipe_count);
int		execute_multiple_pipes(t_token *tokens, t_env *env, int pipe_count);

char	**ft_add_null(char **args);
void	free_str_array(char **arr);
int		handle_cmd_not_found(char **args);
int		handle_permission_denied(char **args, char *path);
void	ft_print_cmd_error(char *cmd);
void	setup_child_fds(int input_fd, int output_fd);

char	*get_path_env(char **envp);
char	*get_path_from_env_list(t_env *env);
char	*get_path_from_env_simple(void);

void	ignore_exec_signals(void);

#endif
