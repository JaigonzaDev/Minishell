/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:01:34 by mergarci          #+#    #+#             */
/*   Updated: 2025/10/14 20:07:12 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "pipes.h"

/*
 * Convierte una lista de tokens en un array de strings para execve
 */
char **tokens_to_args(t_token *tokens) {
  t_token *current;
  char **args;
  int count;
  int i;

  if (!tokens)
    return (NULL);

  // Contar tokens que son comandos o argumentos (ignorar tokens vacíos)
  count = 0;
  current = tokens;
  while (current) {
    if ((current->type == E_COMMAND || current->type == E_ARG) && 
        current->token != NULL && current->token[0] != '\0')
      count++;
    current = current->next;
  }

  // Crear array de strings
  args = (char **)ft_calloc(count + 1, sizeof(char *));
  if (!args)
    return (NULL);

  // Llenar array (solo incluir tokens no vacíos)
  i = 0;
  current = tokens;
  while (current && i < count) {
    if ((current->type == E_COMMAND || current->type == E_ARG) && 
        current->token != NULL && current->token[0] != '\0') {
      args[i] = ft_strdup(current->token);
      i++;
    }
    current = current->next;
  }
  args[i] = NULL;

  return (args);
}

/*
 * Configura las redirecciones basándose en los tokens
 */
int setup_redirections(t_token *tokens, int *input_fd, int *output_fd) {
  t_token *current;
  t_token *prev;

  *input_fd = STDIN_FILENO;
  *output_fd = STDOUT_FILENO;

  current = tokens;
  prev = NULL;

  while (current) {
    // Procesar redirecciones basándose en el token anterior
    if (prev && current->type == E_FILE) {
      if (prev->type == E_REDIRECT_IN) {
        // Redirección de entrada: < archivo
        *input_fd = ft_openfil(current->token, O_RDONLY);
        if (*input_fd == -1) {
          ft_printf("minishell: %s: No such file or directory\n",
                    current->token);
          return (-1);
        }
      } else if (prev->type == E_REDIRECT_OUT) {
        // Redirección de salida: > archivo
        *output_fd = ft_openfil(current->token, O_CREAT | O_WRONLY | O_TRUNC);
        if (*output_fd == -1) {
          ft_printf("minishell: %s: Permission denied\n", current->token);
          return (-1);
        }
      } else if (prev->type == E_REDIRECT_APPEND) {
        // Redirección append: >> archivo
        *output_fd = ft_openfil(current->token, O_CREAT | O_WRONLY | O_APPEND);
        if (*output_fd == -1) {
          ft_printf("minishell: %s: Permission denied\n", current->token);
          return (-1);
        }
      } else if (prev->type == E_REDIRECT_HEREDOC) {
        // Here document: << delimitador
        int heredoc_fd[2];
        if (pipe(heredoc_fd) == -1) {
          perror("pipe");
          return (-1);
        }

        ft_heredoc(heredoc_fd, current->token);
        *input_fd = heredoc_fd[0];
        close(heredoc_fd[1]);
      }
    }

    prev = current;
    current = current->next;
  }

  return (0);
}

/*
 * Ejecuta un comando simple (sin pipes)
 */
static int execute_simple_command(t_token *tokens, t_env *env) {
  char **args;
  int input_fd, output_fd;
  int status;
  pid_t pid;

  // Configurar redirecciones
  if (setup_redirections(tokens, &input_fd, &output_fd) == -1)
    return (1);

  // Convertir tokens a argumentos
  args = tokens_to_args(tokens);
  if (!args || !args[0])
    return (1);

  // Verificar si es un builtin
  if (ft_is_builtin(args[0])) {
    // Redirigir si es necesario
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (input_fd != STDIN_FILENO)
      dup2(input_fd, STDIN_FILENO);
    if (output_fd != STDOUT_FILENO)
      dup2(output_fd, STDOUT_FILENO);

    // Expandir $? justo antes de ejecutar el builtin
    char **expanded_args = expand_exit_status_in_args(args);
    if (expanded_args) {
      // Liberar args originales
      int i = 0;
      while (args[i]) {
        free(args[i]);
        i++;
      }
      free(args);
      args = expanded_args;
    }

    // Ejecutar builtin
    status = ft_execute_builtin(args, &env);

    // Restaurar FDs
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
  } else {
    // Reconstruir comando completo con argumentos
    char *full_command = NULL;
    int i = 0;
    while (args[i]) {
      if (i == 0)
        full_command = ft_strdup(args[i]);
      else {
        char *temp = ft_strjoin(full_command, " ");
        free(full_command);
        full_command = ft_strjoin(temp, args[i]);
        free(temp);
      }
      i++;
    }

    // Ejecutar comando externo
    pid = fork();
    if (pid == 0) {
      // Proceso hijo
      if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
      }
      if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
      }

      // Buscar el comando en PATH
      char *command_path = find_command_in_path(args[0], NULL, env);
      if (!command_path) {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
      }

      // Preparar environment
      char **prepared_envp = prepare_envp(NULL, env);

      // Ejecutar con execve
      if (execve(command_path, args, prepared_envp) == -1) {
        perror("execve");
        exit(126);
      }

      // Este punto nunca se alcanza si execve tiene éxito
      exit(EXIT_FAILURE);
    } else if (pid > 0) {
      // Proceso padre
      signal(SIGINT, SIG_IGN);
      signal(SIGQUIT, SIG_IGN);
      waitpid(pid, &status, 0);

      if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGINT)
          write(STDOUT_FILENO, "\n", 1);
        else if (WTERMSIG(status) == SIGQUIT)
          write(STDOUT_FILENO, "Quit: 3\n", 8);
      }
      status = WEXITSTATUS(status);
      main_signal_config();
    } else {
      perror("fork");
      status = 1;
    }

    free(full_command);
  }

  // Limpiar
  if (input_fd != STDIN_FILENO)
    close(input_fd);
  if (output_fd != STDOUT_FILENO)
    close(output_fd);

  // Liberar memoria
  int i = 0;
  while (args[i]) {
    free(args[i]);
    i++;
  }
  free(args);

  return (status);
}

/*
 * Cuenta el número de pipes en la lista de tokens
 */
static int count_pipes(t_token *tokens) {
  t_token *current;
  int count;

  count = 0;
  current = tokens;
  while (current) {
    if (current->type == E_PIPE)
      count++;
    current = current->next;
  }
  return (count);
}

/*
 * Obtiene los tokens de un grupo específico (separado por pipes)
 */
static t_token *get_group_tokens(t_token *tokens, int group) {
  t_token *current;
  t_token *group_start;
  t_token *new_list;
  t_token *new_current;

  current = tokens;
  group_start = NULL;

  // Encontrar el inicio y fin del grupo
  while (current) {
    if (current->exec_group.group == group && current->type != E_PIPE) {
      if (!group_start)
        group_start = current;
    }
    current = current->next;
  }

  if (!group_start)
    return (NULL);

  // Crear nueva lista para este grupo
  new_list = NULL;
  new_current = NULL;
  current = group_start;

  while (current && current->exec_group.group == group) {
    if (current->type != E_PIPE) {
      t_token *new_token = (t_token *)ft_calloc(1, sizeof(t_token));
      if (!new_token)
        return (NULL);

      new_token->token = ft_strdup(current->token);
      new_token->type = current->type;
      new_token->exec_group = current->exec_group;
      new_token->position = current->position;
      new_token->next = NULL;
      new_token->prev = new_current;

      if (!new_list)
        new_list = new_token;
      else
        new_current->next = new_token;

      new_current = new_token;
    }
    current = current->next;
  }

  return (new_list);
}

// free_token_list ahora está definida en tokens/utils.c

/*
 * Ejecuta un comando en un pipe
 */
static int execute_pipe_command(t_token *tokens, t_env *env, int input_fd,
                                int output_fd) {
  char **args;
  pid_t pid;
  int status;

  if (!tokens)
    return (1);

  // Configurar redirecciones primero
  int redir_input_fd, redir_output_fd;
  if (setup_redirections(tokens, &redir_input_fd, &redir_output_fd) == -1)
    return (1);

  // Si hay redirecciones, usarlas en lugar de los FDs de pipe
  if (redir_input_fd != STDIN_FILENO)
    input_fd = redir_input_fd;
  if (redir_output_fd != STDOUT_FILENO)
    output_fd = redir_output_fd;

  args = tokens_to_args(tokens);
  if (!args || !args[0])
    return (1);

  // Verificar si es un builtin
  if (ft_is_builtin(args[0])) {
    // Para built-ins en pipes, necesitamos manejar FDs
    int saved_stdin = dup(STDIN_FILENO);
    int saved_stdout = dup(STDOUT_FILENO);

    if (input_fd != STDIN_FILENO)
      dup2(input_fd, STDIN_FILENO);
    if (output_fd != STDOUT_FILENO)
      dup2(output_fd, STDOUT_FILENO);

    status = ft_execute_builtin(args, &env);

    // Restaurar FDs
    dup2(saved_stdin, STDIN_FILENO);
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdin);
    close(saved_stdout);
  } else {
    // Comando externo
    pid = fork();
    if (pid == 0) {
      // Proceso hijo
      if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
      }
      if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
      }

      // Buscar el comando en PATH
      char *command_path = find_command_in_path(args[0], NULL, env);
      if (!command_path) {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
      }

      // Preparar environment
      char **prepared_envp = prepare_envp(NULL, env);

      // Ejecutar con execve
      if (execve(command_path, args, prepared_envp) == -1) {
        perror("execve");
        exit(126);
      }

      // Este punto nunca se alcanza si execve tiene éxito
      exit(EXIT_FAILURE);
    } else if (pid > 0) {
      waitpid(pid, &status, 0);
      status = WEXITSTATUS(status);
    } else {
      perror("fork");
      status = 1;
    }
  }

  // Limpiar file descriptors de redirección
  if (redir_input_fd != STDIN_FILENO)
    close(redir_input_fd);
  if (redir_output_fd != STDOUT_FILENO)
    close(redir_output_fd);

  // Liberar memoria
  int i = 0;
  while (args[i]) {
    free(args[i]);
    i++;
  }
  free(args);

  return (status);
}

/*
 * Ejecuta un pipeline completo con múltiples pipes
 */
static int execute_multiple_pipes(t_token *tokens, t_env *env, int pipe_count) {
  int **pipes;
  pid_t *pids;
  int i;
  int status;

  int final_status;

  // Crear arrays para pipes y PIDs
  pipes = (int **)ft_calloc(pipe_count, sizeof(int *));
  pids = (pid_t *)ft_calloc(pipe_count + 1, sizeof(pid_t));

  if (!pipes || !pids)
    return (1);

  // Crear todos los pipes
  for (i = 0; i < pipe_count; i++) {
    pipes[i] = (int *)ft_calloc(2, sizeof(int));
    if (!pipes[i] || pipe(pipes[i]) == -1) {
      perror("pipe");
      return (1);
    }
  }

  // Ejecutar cada comando en el pipeline
  for (i = 0; i <= pipe_count; i++) {
    t_token *group_tokens = get_group_tokens(tokens, i);
    if (!group_tokens)
      continue;

    pids[i] = fork();
    if (pids[i] == 0) {
      // Proceso hijo
      child_signal_config();
      int input_fd = STDIN_FILENO;
      int output_fd = STDOUT_FILENO;

      // Configurar input (del pipe anterior)
      if (i > 0) {
        input_fd = pipes[i - 1][0];
        printf("DEBUG: Proceso %d usando input_fd = %d (pipe anterior)\n", i,
               input_fd);
      }

      // Configurar output (al siguiente pipe)
      if (i < pipe_count) {
        output_fd = pipes[i][1];
      }

      // Cerrar todos los pipes no necesarios
      int j;
      for (j = 0; j < pipe_count; j++) {
        if (j != i - 1)
          close(pipes[j][0]);
        if (j != i)
          close(pipes[j][1]);
      }

      // Configurar redirecciones si las hay
      int redir_input, redir_output;
      if (setup_redirections(group_tokens, &redir_input, &redir_output) == 0) {
        if (redir_input != STDIN_FILENO)
          input_fd = redir_input;
        if (redir_output != STDOUT_FILENO)
          output_fd = redir_output;
      }

      // Ejecutar el comando
      status = execute_pipe_command(group_tokens, env, input_fd, output_fd);

      free_token_list(group_tokens);
      exit(status);
    } else if (pids[i] < 0) {
      perror("fork");
      free_token_list(group_tokens);
      return (1);
    }

    free_token_list(group_tokens);
  }

  // Cerrar todos los pipes en el proceso padre
  for (i = 0; i < pipe_count; i++) {
    close(pipes[i][0]);
    close(pipes[i][1]);
    free(pipes[i]);
  }

  // Esperar a todos los procesos hijo
  final_status = 0;
  signal(SIGINT, SIG_IGN);
  signal(SIGQUIT, SIG_IGN);
  for (i = 0; i <= pipe_count; i++) {
    if (pids[i] > 0) {
      waitpid(pids[i], &status, 0);
      if (i == pipe_count) // El último comando determina el status final
      {
        if (WIFSIGNALED(status)) {
          if (WTERMSIG(status) == SIGINT)
            write(STDOUT_FILENO, "\n", 1);
          else if (WTERMSIG(status) == SIGQUIT)
            write(STDOUT_FILENO, "Quit: 3\n", 8);
          final_status = 128 + WTERMSIG(status); // Set status based on signal
        } else {
          final_status = WEXITSTATUS(status);
        }
      }
    }
  }

  free(pipes);
  free(pids);
  main_signal_config();
  return (final_status);
}

/*
 * Función principal para ejecutar pipeline
 */
int execute_pipeline(t_token *tokens, t_env *env) {
  int pipe_count;

  if (!tokens)
    return (1);

  pipe_count = count_pipes(tokens);

  // Si no hay pipes, ejecutar comando simple
  if (pipe_count == 0)
    return (execute_simple_command(tokens, env));

  // Ejecutar pipeline con múltiples pipes
  return (execute_multiple_pipes(tokens, env, pipe_count));
}
