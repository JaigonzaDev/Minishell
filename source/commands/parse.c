/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:32:11 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/20 17:57:20 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Identifica el tipo de redirección basándose en el token
 */
static int identify_redirection(char *token)
{
    if (!token)
        return (0);
    
    if (ft_strncmp(token, ">>", 2) == 0)
        return (E_REDIRECT_APPEND);
    else if (ft_strncmp(token, "<<", 2) == 0)
        return (E_REDIRECT_HEREDOC);
    else if (token[0] == '>' && ft_strlen(token) == 1)
        return (E_REDIRECT_OUT);
    else if (token[0] == '<' && ft_strlen(token) == 1)
        return (E_REDIRECT_IN);
    // NO procesar pipes aquí - se procesan en process_pipes
    
    return (0);
}

/*
 * Marca un token como archivo de redirección
 */
static void mark_redirection_file(t_token *redirect_token, t_token *file_token, int redirect_type)
{
    if (!redirect_token || !file_token)
        return;
    
    // Marcar el token de redirección
    redirect_token->type = redirect_type;
    
    // Marcar el siguiente token como archivo
    if (!is_operator(*file_token))
    {
         file_token->type = E_FILE;
     
        // Configurar I/O según el tipo de redirección
	    if ((redirect_type == E_REDIRECT_OUT) || (redirect_type == E_REDIRECT_APPEND))
	        file_token->exec_group.io = E_STDOUT;
	    else if ((redirect_type == E_REDIRECT_IN) || (redirect_type == E_REDIRECT_HEREDOC))
            file_token->exec_group.io = E_STDIN;
    }
}

/*
 * Procesa las redirecciones en la lista de tokens
 */
static void process_redirections(t_token *tokens)
{
    t_token *current;
    int redirect_type;
    
    current = tokens;
    while (current)
    {
        redirect_type = identify_redirection(current->token);
        if (current->type == 0)
            current->type = redirect_type;
        if (redirect_type && current->next && identify_redirection(current->next->token) == 0)
        {
            if (redirect_type == E_REDIRECT_HEREDOC && current->next->next)
                mark_redirection_file(current, current->next->next, redirect_type);
            else
                mark_redirection_file(current, current->next, redirect_type);
            if (!is_operator(*current->next))
                current = current->next; // Saltar el archivo
        }
        
        current = current->next;
    }
}
/*
    Error syntax in pipes:
    1. No prev token
    2. No next token
    3. Prev token or Next token = redirection or pipe
*/

// int check_syntax_pipes(t_token *token)
// {
//     t_token *current;

//     current = token;
//     if (!current->prev) 
//         return (1);
//     if (!current->next) 
//         return (1);
//     if (ft_strnstr(current->prev->token == "|><>><<") || ft_strnkey(current->next->token == "|><>><<"))
//         return (1);
//     return (0);
// }
/*
 * Marca los pipes en la lista de tokens
 */
static void process_pipes(t_token *tokens)
{
    t_token *current;
    int group;
    
    current = tokens;
    group = 0;
    // Primero, identificar y marcar los pipes
    while (current)
    {
        if (current->token && current->token[0] == '|' && 
            ft_strlen(current->token) == 1)
        {
            current->type = E_PIPE;
        }
        current = current->next;
    }
    // Luego, asignar grupos
    current = tokens;
    while (current)
    {
        current->exec_group.group = group;
        
        if (current->type == E_PIPE)
        {
            group++;
        }
        current = current->next;
    }
}

/*
 * Identifica comandos y argumentos
 */
static void process_commands_and_args(t_token *tokens)
{
    t_token *current;
    int expecting_command;
    
    current = tokens;
    expecting_command = 1;
    
    while (current)
    {
        // Si no es redirección, pipe o archivo, es comando o argumento
        if (current->type == 0)
        {
            if (expecting_command)
            {
                current->type = E_COMMAND;
                expecting_command = 0;
            }
            else
            {
                current->type = E_ARG;
            }
        }
        
        // Después de un pipe, esperamos un nuevo comando
        if (current->type == E_PIPE)
        {
            expecting_command = 1;
        }
        
        current = current->next;
    }
}

int syntax_error(char *token_value, int type)
{
    if (type == E_ERROR_UNEXPECTED)
    {
        fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", token_value);
        return (258);
    }
    else if (type == E_ERROR_MISSING_FILE)
    {
        fprintf(stderr, "minishell: %s: No such File or Directory \n", token_value);
        return (1);
    }
    return (1);
}
int is_redirection(t_token token)
{
    if (token.lit == 1)
        return (FALSE);
    if (token.type == E_REDIRECT_IN)
        return (TRUE);
    if (token.type == E_REDIRECT_OUT)
        return (TRUE);
    if (token.type == E_REDIRECT_APPEND)
        return (TRUE);
    if (token.type == E_REDIRECT_HEREDOC)
        return (TRUE);
    return (FALSE);

}

int is_operator(t_token token)
{
    if (token.lit == 1)
        return (FALSE);
    if (token.type == E_PIPE || is_redirection(token))
        return (1);
    return (0);
}

int is_word(int type)
{
    if (type == E_ARG || type == E_COMMAND)
        return (1);
    return (0);
}

int correct_syntax(t_token *tokens)
{
    t_token      *current = tokens;
    int state;

    state = E_STATE_EXPECT_CMD;
    // Si la línea está vacía, no hay error.
    if (current == NULL || current->token == NULL || *current->token == '\0')
        return (0);

    while (current != NULL)
    {
        if (state == E_STATE_EXPECT_CMD)
        {
            if (is_word(current->type))
                state = E_STATE_EXPECT_ARG;
            else if (is_redirection(*current))
                state = E_STATE_EXPECT_FILENAME;
            else if (current->type == E_PIPE)
                return (syntax_error(current->token, E_ERROR_UNEXPECTED));
        }
        else if (state == E_STATE_EXPECT_ARG)
        {
            if (is_word(current->type))
                state = E_STATE_EXPECT_ARG;
            else if (is_redirection(*current))
            {
                if (current->type == E_REDIRECT_HEREDOC)
                    state = E_STATE_EXPECT_DELIMITER;
                else
                    state = E_STATE_EXPECT_FILENAME;
            }
            else if (current->type == E_PIPE)
                state = E_STATE_EXPECT_CMD;
        }
        else if (state == E_STATE_EXPECT_FILENAME)
        {
            if (current->type == E_FILE)
            {
                if (current->exec_group.io == E_STDIN && open(current->token, O_RDONLY) == -1)
                    return (syntax_error(current->token, E_ERROR_MISSING_FILE));
            }
            if (is_word(current->type))
                state = E_STATE_EXPECT_ARG;
            else if (is_operator(*current))
                return (syntax_error(current->token, E_ERROR_UNEXPECTED));
            else if (current->type == E_PIPE)
                state = E_STATE_EXPECT_CMD;
        }
        else if (state == E_STATE_EXPECT_DELIMITER)
        {
            if (is_word(current->type))
                state = E_STATE_EXPECT_FILENAME;
        }
        current = current->next;
    }
    if (state == E_STATE_EXPECT_FILENAME || state == E_STATE_EXPECT_CMD)
        return (syntax_error("newline", E_ERROR_UNEXPECTED));
    return (0);
}

/*
 * Función principal de parsing mejorada
 */
int parse_commands_new(t_token **tokens)
{
    if (!tokens || !*tokens)
        return (1);
    
    // Paso 1: Procesar pipes y asignar grupos (PRIMERO)
    process_pipes(*tokens);
    
    // Paso 2: Procesar redirecciones
    process_redirections(*tokens);
    
    // Paso 3: Identificar comandos y argumentos
    process_commands_and_args(*tokens);
    debug_parsing(*tokens);

    // Paso 4: Check syntax (returns exit code)
    return (correct_syntax(*tokens));
}

/*
 * Función auxiliar para debugging del parsing
 */
void debug_parsing(t_token *tokens)
{
    t_token *current;
    const char *type_names[] = {
        "COMMAND", "ARG", "FILE", "REDIRECT_OUT", "REDIRECT_IN", 
        "REDIRECT_APPEND", "REDIRECT_HEREDOC", "PIPE"
    };
    
    current = tokens;
    while (current)
    {
        printf("Token: '%s' | Type: %s | Group: %d | IO: %d | Pos: %d\n",
               current->token,
               (current->type < 8) ? type_names[current->type] : "UNKNOWN",
               current->exec_group.group,
               current->exec_group.io,
               current->position);
        current = current->next;
    }
}

