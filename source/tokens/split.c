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

/*
 * Divide un token por espacios/tabs creando múltiples tokens
 * Retorna el primer token de la secuencia creada
 */
static t_token *split_token_by_spaces(t_token *token)
{
	char *str;
	char *start;
	t_token *new_token;
	t_token *first_new;
	t_token *prev_token;
	int in_word;

	if (!token || !token->token)
		return (token);
	
	str = token->token;
	first_new = NULL;
	prev_token = NULL;
	in_word = 0;
	start = str;

	// Procesar cada carácter
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
		{
			// Fin de una palabra
			if (in_word)
			{
				new_token = malloc(sizeof(t_token));
				if (!new_token)
					return (token); // Error: mantener token original
				ft_memset(new_token, 0, sizeof(t_token));
				new_token->token = ft_substr(start, 0, str - start);
				new_token->type = token->type;
				new_token->position = token->position;
				new_token->lit = 0;
				
				if (!first_new)
					first_new = new_token;
				if (prev_token)
					prev_token->next = new_token;
				new_token->prev = prev_token;
				prev_token = new_token;
				in_word = 0;
			}
		}
		else
		{
			// Inicio de una palabra
			if (!in_word)
			{
				start = str;
				in_word = 1;
			}
		}
		str++;
	}
	
	// Última palabra si existe
	if (in_word)
	{
		new_token = malloc(sizeof(t_token));
		if (!new_token)
			return (token); // Error: mantener token original
		ft_memset(new_token, 0, sizeof(t_token));
		new_token->token = ft_substr(start, 0, str - start);
		new_token->type = token->type;
		new_token->position = token->position;
		new_token->lit = 0;
		
		if (!first_new)
			first_new = new_token;
		if (prev_token)
			prev_token->next = new_token;
		new_token->prev = prev_token;
		prev_token = new_token;
	}
	
	// Si no se crearon nuevos tokens (solo espacios), eliminar token
	if (!first_new)
	{
		// Conectar prev con next
		if (token->prev)
			token->prev->next = token->next;
		if (token->next)
			token->next->prev = token->prev;
		
		// Liberar token original
		free(token->token);
		free(token);
		
		return (NULL);
	}
	
	// Conectar con tokens siguientes
	if (token->next)
	{
		prev_token->next = token->next;
		token->next->prev = prev_token;
	}
	
	// Conectar con tokens anteriores
	if (token->prev)
	{
		token->prev->next = first_new;
		first_new->prev = token->prev;
	}
	
	// Liberar token original
	free(token->token);
	free(token);
	
	return (first_new);
}

/*
 * Aplica word splitting a todos los tokens que no sean literales
 */
t_token *apply_word_splitting(t_token *tokens)
{
	t_token *current;
	t_token *next;
	t_token *new_head;
	int has_spaces;
	char *str;

	if (!tokens)
		return (NULL);
	
	current = tokens;
	new_head = tokens;
	
	while (current)
	{
		next = current->next;
		
		// Solo hacer word splitting si NO es literal y tiene espacios/tabs
		if (current->lit == 0 && current->token)
		{
			has_spaces = 0;
			str = current->token;
			while (*str)
			{
				if (*str == ' ' || *str == '\t')
				{
					has_spaces = 1;
					break;
				}
				str++;
			}
			
			if (has_spaces)
			{
				t_token *first_split = split_token_by_spaces(current);
				
				// Si split retornó NULL (token solo con espacios), se eliminó
				if (!first_split)
				{
					// Si current era el head, actualizar al siguiente
					if (current == new_head)
						new_head = next;
				}
				else
				{
					// Si current era el head, actualizar
					if (current == new_head)
						new_head = first_split;
				}
				
				current = next;
				continue;
			}
		}
		
		current = next;
	}
	
	return (new_head);
}