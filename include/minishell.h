/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:12:34 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/27 10:56:01 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

// Project headers
#include "environment.h"
#include "builtins.h"


//main.c
//main function
# define TRUE 1
# define FALSE 0

typedef enum e_prompt
{
    E_PROMPT_MAIN,
    E_PROMPT_SQUOTE,
    E_PROMPT_DQUOTE,
    E_PROMPT_BQUOTE,
    E_PROMPT_MAX
} t_prompt;

typedef enum e_io
{
    E_STDIN,
    E_STDOUT,
} t_io;
typedef enum e_type
{
    E_COMMAND,
    E_ARG,
    E_FILE,
    E_REDIRECT_OUT,     // >
    E_REDIRECT_IN,      // <
    E_REDIRECT_APPEND,  // >>
    E_REDIRECT_HEREDOC, // <<
    E_PIPE,             // |
    E_REDIRECT
} t_type;

typedef enum e_expect
{
    E_STATE_EXPECT_CMD,
    E_STATE_EXPECT_ARG,
    E_STATE_EXPECT_RED,
    E_STATE_EXPECT_PIPE,
    E_STATE_EXPECT_FILENAME,
    E_STATE_EXPECT_DELIMITER,
} t_expect;
// t_env definido en environment.h

typedef enum e_error
{
    E_ERROR_UNEXPECTED,
    E_ERROR_MISSING_FILE,
} t_error;
typedef struct s_group
{
    t_io io; 
    int group;
}t_group;

typedef struct s_global
{
    int last_signal;
    int shell_mode;
} t_global;
extern t_global g_status;
typedef struct s_token
{
    char *token;
    int lit; // TOMAR LA STRING COMO LITERAL (CASO DE QUE HAYA | "|" Tiene que intentar ejecutar |)
    t_group exec_group;
    int type;
    int position;
    struct s_token *next;
    struct s_token *prev;
} t_token;

int quoting(char **line, t_token **token, t_env *env);
void case_dquote(char **line, t_token **token, t_env *env);
void case_backtick(char **line, t_token **token, t_env *env);
void case_squote(char **line, t_token **token);
void case_backlash(char **line, t_token **token);
void case_dollar(char **line, t_token **token, t_env *env);
char *search_env_var(char *key, t_env *env);

// Command substitution and expansion
char *execute_command_capture_output(char *command, t_env *env);
char *get_exit_status_string(void);
void update_exit_status(int status);
char *process_command_substitution(char *command, t_env *env);
char *process_backtick_substitution(char *command, t_env *env);
char *expand_exit_status_in_string(char *str);
char **expand_exit_status_in_args(char **args);

// Global variable for exit status
extern int g_last_exit_status;

// Main execution function
int bash_execute(t_token *tokens, t_env *env);



char *read_line(int type);
int ft_putstr(char *s, char **buf);
int ft_putchar(char c, char **s);
void main_signal_config(void);
void child_signal_config(void);
void child_handler(int signum);
void parent_handler(int signum);

const char * prompt(int type);
int parse_commands_new(t_token **tokens);
void debug_parsing(t_token *tokens);
t_token *bash_split(char **line, t_env *env);
void debug(t_token *tokens);
void delete_node(t_token **tokens, t_token **tmp);
void free_token_list(t_token *tokens);
char *separate_operators(char *input);
int is_operator(t_token token);
#endif