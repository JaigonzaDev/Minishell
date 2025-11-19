/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minishell                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 00:00:00 by minishell         #+#    #+#             */
/*   Updated: 2025/10/08 00:00:00 by minishell        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

# include "minishell.h"
# include "get_next_line_bonus.h"
# include <sys/wait.h>
# include <fcntl.h>

# define READ 0 
# define WRITE 1 
# define I 0
# define O 1
# define MAX_PIPES 1024

// pipes_bonus.c
int		ft_pipeline(int *files, char **commands, char **envp);

// inputs_bonus.c
int		check_exec(char *command, char **envp, int status);

// utils_bonus.c
void	ft_print_help(void);
int		ft_count_string(char **string);
void	ft_create_fd(int *fd);
void	ft_heredoc(int *files, char *limit);

// split_bonus.c
char	**ft_split_bash(char *str);

// utils_fd_bonus.c
void	ft_dup_close(int fd1, int fd2, int fd_close);
void	ft_closefd(int fd);
void	ft_parent_fd(int *fd, int *fd_saved);
void	ft_close_fds(int *fd1, int *fd2);
int		ft_openfil(char *name_file, int open_mode);

// Nuevas funciones para integración con minishell
int		execute_pipeline(t_token *tokens, t_env *env);
int		setup_redirections(t_token *tokens, int *input_fd, int *output_fd);
char	**tokens_to_args(t_token *tokens);

// Funciones auxiliares incluidas en libft

// path_utils.c - Búsqueda optimizada en PATH
char	*find_command_in_path(char *command, char **envp, t_env *env);
int		is_command_executable(char *path);
char	**prepare_envp(char **envp, t_env *env);

#endif
