#include "minishell.h"

int ft_putchar(char c, char **s)
{
    char *new_str;
    size_t len;

    if (*s == NULL)
    {
        // Crear una nueva cadena si no existe
        new_str = malloc(2 * sizeof(char)); // Espacio para el carácter y '\0'
        if (!new_str)
            return (-1); // Error de memoria
        new_str[0] = c;
        new_str[1] = '\0';
    }
    else
    {
        // Realocar memoria para agregar el nuevo carácter
        len = strlen(*s);
        new_str = malloc((len + 2) * sizeof(char)); // Espacio para la cadena existente, el nuevo carácter y '\0'
        if (!new_str)
            return (-1); // Error de memoria
        strcpy(new_str, *s); // Copiar la cadena existente
        new_str[len] = c;    // Agregar el nuevo carácter
        new_str[len + 1] = '\0';
        free(*s);            // Liberar la memoria de la cadena original
    }
    *s = new_str; // Actualizar el puntero original
    return (0); // Éxito
}

int ft_putstr(char *s, char **buf)
{
	while (*s)
	{
		if (ft_putchar(*s, buf) == -1)
			return (-1); // Error de memoria
		s++;
	}
	return (0); // Éxito
}

/*
 * Libera una lista completa de tokens
 */
void free_token_list(t_token *tokens)
{
    t_token *current;
    t_token *next;
    
    current = tokens;
    while (current)
    {
        next = current->next;
        if (current->token)
            free(current->token);
        free(current);
        current = next;
    }
}