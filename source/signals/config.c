#include "minishell.h"


void parent_handler(int signum)
{
    (void)signum;
    write(STDOUT_FILENO, "\n", 1); // Salto de línea
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

// Manejador de SIGINT para el proceso hijo
void child_handler(int signum)
{
    (void)signum;
    // printf ("PROCESO HIJO\n");
    // write(STDOUT_FILENO, "\n", 1); // Salto de línea
    exit(130);     
}

void main_signal_config(void)
{
    struct sigaction sa;

    // rl_catch_signals = 0;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = parent_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}

void child_signal_config(void)
{
	struct sigaction	sa;

    memset(&sa, 0, sizeof(sa));
    // sa.sa_flags = SA_RESTART;
    sa.sa_handler = child_handler;
    sigaction(SIGINT, &sa, NULL);
}
