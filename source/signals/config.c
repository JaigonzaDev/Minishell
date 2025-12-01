#include "minishell.h"

void parent_handler(int signum) {
  (void)signum;
  g_status.last_signal = SIGINT;
  write(STDOUT_FILENO, "\n", 1);
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
}

void child_handler(int signum) {
  (void)signum;
  write(STDOUT_FILENO, "\n", 1);
  exit(130);
}

void quit_handler(int signum) {
  (void)signum;
  if (rl_line_buffer && strlen(rl_line_buffer) > 0) {
    rl_replace_line("", 0);
    rl_redisplay();
    ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
    exit(131);
  }
  rl_on_new_line();
  rl_redisplay();
}

void main_signal_config(void) {
  struct sigaction sa;

  // rl_catch_signals = 0; // This might be needed depending on readline
  // version, but let's try without first or check headers
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = parent_handler;
  sa.sa_flags = SA_RESTART;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, NULL);

  sa.sa_handler = SIG_IGN;
  sigaction(SIGQUIT, &sa, NULL);
}

void child_signal_config(void) {
  struct sigaction sa;

  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = SIG_DFL;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  sigaction(SIGINT, &sa, NULL);
  sigaction(SIGQUIT, &sa, NULL);
}
