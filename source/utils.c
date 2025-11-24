#include "minishell.h"

void debug(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("----\n");
		printf("Token: %s, Type: %d, Exec Group: %d, Num IO: %d, Position: %d\n", tokens->token, tokens->type, tokens->exec_group.group, tokens->exec_group.io, tokens->position);
		printf("----\n");
		tokens = tokens->next;
	}
}

const char *prompt(int type)
{
    static int flag = 0;
    if (errno == EINTR && flag == 0)
    {
        // rl_on_new_line();
        // rl_replace_line("", 0);
        // write(1, "", 1);
        errno = 0;
        flag++;
        return "";
    }
    if (type == E_PROMPT_MAIN)
        return "bash-mini$ ";
    else if (type == E_PROMPT_SQUOTE)
        return "squote> ";
    else if (type == E_PROMPT_DQUOTE)
        return "dquote> ";
    else if (type == E_PROMPT_BQUOTE)
        return "bquote> ";
    return "";
}