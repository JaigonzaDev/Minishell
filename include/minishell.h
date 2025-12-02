/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:12:34 by mergarci          #+#    #+#             */
/*   Updated: 2025/12/01 18:51:12 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "builtins.h"
#include "environment.h"
#include "libft.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

typedef enum e_prompt {
  E_PROMPT_MAIN,
  E_PROMPT_SQUOTE,
  E_PROMPT_DQUOTE,
  E_PROMPT_BQUOTE,
  E_PROMPT_MAX
} t_prompt;

typedef enum e_io {
  E_STDIN,
  E_STDOUT,
} t_io;

typedef enum e_type {
  E_COMMAND,
  E_ARG,
  E_FILE,
  E_REDIRECT_OUT,
  E_REDIRECT_IN,
  E_REDIRECT_APPEND,
  E_REDIRECT_HEREDOC,
  E_PIPE,
  E_REDIRECT
} t_type;

typedef enum e_expect {
  E_STATE_EXPECT_CMD,
  E_STATE_EXPECT_ARG,
  E_STATE_EXPECT_RED,
  E_STATE_EXPECT_PIPE,
  E_STATE_EXPECT_FILENAME,
  E_STATE_EXPECT_DELIMITER,
} t_expect;

typedef enum e_error {
  E_ERROR_UNEXPECTED,
  E_ERROR_MISSING_FILE,
} t_error;

typedef struct s_group {
  t_io io;
  int group;
} t_group;

typedef struct s_global {
  int last_signal;
  int shell_mode;
  int exit_flag;
} t_global;

extern t_global g_status;

typedef struct s_token {
  char *token;
  int lit;
  t_group exec_group;
  int type;
  int position;
  struct s_token *next;
  struct s_token *prev;
} t_token;

typedef struct s_split_context {
	t_token *first;
	t_token *prev;
	char *start;
	int in_word;
} t_split_context;


extern int g_last_exit_status;

int quoting(char **line, t_token **token, t_env *env);
void case_dquote(char **line, t_token **token, t_env *env);
void case_backtick(char **line, t_token **token, t_env *env);
void case_squote(char **line, t_token **token);
void case_backlash(char **line, t_token **token);
void case_dollar(char **line, t_token **token, t_env *env);
char *search_env_var(char *key, t_env *env);
char *execute_command_capture_output(char *command, t_env *env);
char *get_exit_status_string(void);
void update_exit_status(int status);
char *process_command_substitution(char *command, t_env *env);
char *process_backtick_substitution(char *command, t_env *env);
pid_t setup_command_fork(char *command, t_env *env, int pipefd[2]);
void trim_trailing_newline(char *output);
void exec_child_process(char *command, t_env *env, int pipefd[2]);
char *read_pipe_output(int fd, pid_t pid);
char *join_expansion_parts(char *before, char *status, char *after);
char *expand_exit_status_in_string(char *str);
char **expand_exit_status_in_args(char **args);
int bash_execute(t_token *tokens, t_env *env);
char *read_line(int type);
int ft_putstr(char *s, char **buf);
int ft_putchar(char c, char **s);
void main_signal_config(void);
void child_signal_config(void);
void child_handler(int signum);
void parent_handler(int signum);
const char *prompt(int type);
int parse_commands_new(t_token **tokens);
void debug_parsing(t_token *tokens);
t_token *bash_split(char **line, t_env *env);
t_token *apply_word_splitting(t_token *tokens);
void debug(t_token *tokens);
void delete_node(t_token **tokens, t_token **tmp);
void free_token_list(t_token *tokens);
char *separate_operators(char *input);
int is_operator(t_token token);
t_token *create_new_token_node(t_token *prev);
t_token *create_split_token(char *start, int len, t_token *orig);
void link_new_token(t_token *new, t_token **first, t_token **prev);
void link_split_tokens(t_token *token, t_token *first_new);
int handle_next_node(t_token **tokens, t_token *head);
int handle_literal_str(char *str, char last);
void skip_spaces(char **line);
void process_split_char(char *str, t_split_context *ctx, t_token *token);
int token_needs_splitting(char *str);
t_token *handle_token_split(t_token *current, t_token *new_head, t_token *next);
t_token *split_token_by_spaces(t_token *token);
t_token *init_split(t_token **head, int *i);
void process_redirections(t_token *tokens);
void process_pipes(t_token *tokens);
int syntax_error(char *token_value, int type);
int is_redirection(t_token token);
int is_word(int type);
int correct_syntax(t_token *tokens);
int handle_expect_cmd(t_token *current, int *state);
int handle_expect_arg(t_token *current, int *state);
int handle_expect_filename(t_token *current, int *state);
int handle_expect_delimiter(t_token *current, int *state);

#endif