/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:12:01 by mergarci          #+#    #+#             */
/*   Updated: 2025/11/27 11:42:50 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"

t_global g_status;

char *read_line(int type) {
  char *buf = NULL;
  // (void)type;

  if (isatty(STDIN_FILENO)) {
    buf = readline(prompt(type));
    if (g_status.last_signal == SIGQUIT) {
      // GUARDAR EXIT(131)
    } else if (g_status.last_signal == SIGINT) {
      // GUARDAR EXIT(130)
    } else if (feof(stdin))
      exit(EXIT_SUCCESS);
    // Guarda en el buffer
    if (buf && buf[0] != '\0')
      add_history(buf);
  } else {
    buf = ft_gnl(STDIN_FILENO, NULL);
    if (buf) {
      int len = ft_strlen(buf);
      if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
    }
  }
  return (buf);
}

int bash_execute(t_token *tokens, t_env *env) {
  int status;

  if (!tokens)
    return (1);

  // Ejecutar usando el sistema de pipes
  status = execute_pipeline(tokens, env);

  return (status);
  // // Actualizar status en variable global para $?
  // update_exit_status(status);
}

int main(int argc, char **argv, char **envp) {
  char *line;
  t_token *tokens;
  t_env *env;
  int status;
  pid_t pid;
  (void)argc;
  (void)argv;

  env = NULL;
  tokens = NULL;
  line = NULL;
  main_signal_config();
  // CARLOS: >Mover env_save antes bucle para que las variables de export
  // persistan<
  env_save(envp, &env);
  while ((line = read_line(E_PROMPT_MAIN))) {
    // Si la línea empieza por '#', se ignora
    if (line[0] == '#') {
      free(line);
      continue;
    }
    // // // Crear un nuevo proceso para manejar la línea
    pid = fork();
    if (pid < 0) {
      perror("fork");
      // continue;
    } else if (pid == 0) {
      child_signal_config();
      // Separar operadores pegados al texto

      char *separated_line = separate_operators(line);
      if (separated_line) {
        free(line);
        line = separated_line;
      }
      tokens = bash_split(&line, env);
      if ((status = parse_commands_new(&tokens)) == 0) {
        debug_parsing(tokens);
        status = bash_execute(tokens, env);
      }
      exit(status);
    } else {
      signal(SIGINT, SIG_IGN);
      waitpid(pid, &status, 0); // Esperar al hijo
      if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGINT)
          write(STDOUT_FILENO, "\n", 1);
        else if (WTERMSIG(status) == SIGQUIT)
          write(STDOUT_FILENO, "Quit: 3\n", 8);
      }
      // CARLOS: >Actualizar el estado de salida después de cada comando<
      update_exit_status(WEXITSTATUS(status));
      main_signal_config();
    }
    // CARLOS: >QUITAR env_freeall de aquí para no liberar en cada iteración<
  }
  // CARLOS: >Mover env_freeall DESPUÉS del bucle para liberar al final del programa<
  env_freeall(&env);
  return (EXIT_SUCCESS);
}
