#include "minishell.h"


void parent_handler(int signum)
{
    (void)signum;
    printf("\n");
    fflush(stdout);
}

// Manejador de SIGINT para el proceso hijo
void child_handler(int signum)
{
    (void)signum;
    printf("\nProceso hijo terminado con Ctrl+C\n");
    exit(EXIT_SUCCESS);
}

void main_signal_config(void)
{
    struct sigaction sa;
    sa.sa_handler = parent_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
}
void child_signal_config(void)
{
	struct sigaction	sa;

    sa.sa_handler = child_handler;
    sigaction(SIGINT, &sa, NULL);
}
