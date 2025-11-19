#include "minishell.h"
t_token *bash_split(char **line, t_env *env)
{
	t_token *tokens;
	t_token *head;
	int i;

	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (NULL);
	ft_memset(tokens, 0, sizeof(t_token));
	tokens->token = NULL;
	tokens->prev = NULL;
	head = tokens;
	i = 0;

	// DIVIDIR LA LINEA EN TOKENS
	while(**line)
	{
		tokens->position = i;
		// SALTAMOS LOS ESPACIOS Y TABULACIONES INICIALES
		while (**line == ' ' || **line == '\t')
			(*line)++;
		while (**line != ' ' && **line != '\t' && **line != '\0')
		{
			if (quoting(line, &tokens, env) == 0)
			{
				if (ft_putchar(**line, &tokens->token) == -1)
				{
					// Error de memoria: liberar y retornar NULL
					free_token_list(head);
					return (NULL);
				}
			}
			(*line)++;
		}
		// AÑADIR EL NODO
		if (**line != '\0')
		{
			tokens->next = malloc(sizeof(t_token));
			if (!tokens->next)
			{
				// Error: liberar toda la lista creada hasta ahora
				free_token_list(head);
				return (NULL);
			}
			ft_memset(tokens->next, 0, sizeof(t_token));
			tokens->next->prev = tokens;
			tokens = tokens->next;
		}
		i++;
	}
	return (head);
}