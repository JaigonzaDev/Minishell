#include "minishell.h"

// void case_backlash(char **line, t_token **token)
// {
// 	// MANEJO DE "\"
// 	(*line)++;
// 	(*token)->lit = 1;
// 	if (ft_putchar(**line, &(*token)->token) == -1)
// 		return; // Error de memoria
// }

void case_squote(char **line, t_token **token)
{
	// Se interpreta lo de dentro literal
	//Se salta la primera comilla
	(*line)++;
	(*token)->lit = 1;
	// SI CIERRA LA SIMPLE COMILLA
	if (**line == '$' && ft_strnstr(*line, "\"",ft_strlen(*line)) != NULL)
	{
		ft_putchar('\'', &(*token)->token);
		return;
	}
	if (ft_strnstr(*line, "\'",ft_strlen(*line)) != NULL)
	{
		while (**line != '\'')
		{
			if (ft_putchar(**line, &(*token)->token) == -1)
				return; // Error de memoria
			(*line)++;
		}
	}
	else
	{
		ft_putchar('\'', &(*token)->token);
	}
	// COMILLA NO CERRADA
	// Espera mas inputs
	// else
	// {
	// 	// Mientras no encontremos una linea que tenga ' guardamos toda la línea.
	// 	while (ft_strnstr(*line, "\'", ft_strlen(*line)) == NULL)
	// 	{
	// 		// Concatenar a la linea anterior
	// 		if (ft_putstr(*line, &(*token)->token) == -1)
	// 			return; // Error de memoria
	// 		*line = read_line(E_PROMPT_SQUOTE);
	// 	}
	// 	// Si encontramos un línea que si lo tenga guardamos hasta encontrar el '
	// 	while (**line != '\'')
	// 	{
	// 		if (ft_putchar(**line, &(*token)->token) == -1)
	// 			return; // Error de memoria
	// 		(*line)++;
	// 	}
	// }
	
}

// SIEMPRE INTENTA EJECUTAR COMO COMANDO LO QUE HAY DENTRO
/*
	Podría guardar los caracteres del comando en un buffer temporal
	y luego ejecutar ese comando y capturar su salida.
	Una vez hecho eso se guardan los caracteres resultantes en el token actual.
	a) SI produce expansión de $.
*/

// void case_backtick(char **line, t_token **token, t_env *env)
// {
// 	char *buf;
// 	buf = NULL;

// 	//Se salta la primera comilla
// 	(*line)++;
// 	// SI CIERRA LA SIMPLE COMILLA
// 	if (ft_strnstr(*line, "`",ft_strlen(*line)) != NULL)
// 	{
// 		while (**line != '`')
// 		{
// 			if (**line == '$')
// 				case_dollar(&buf, token, env);
// 			else
// 				ft_putchar(**line, &buf);
// 			(*line)++;
// 		}
// 	}
// 	// COMILLA NO CERRADA
// 	// Espera mas inputs
// 	else
// 	{
// 		// Mientras no encontremos una linea que tenga ' guardamos toda la línea.
// 		while (ft_strnstr(*line, "`", ft_strlen(*line)) == NULL && **line != '`')
// 		{
// 			// Concatenar a la linea anterior
// 			if (**line == '$')
// 				case_dollar(&buf, token, env);
// 			if (**line != '\0')
// 				ft_putchar(**line, &buf);
// 			else
// 			{
// 				*line = read_line(E_PROMPT_BQUOTE);
// 			}
// 		}
// 	}
// 	// Ejecutar comando entre backticks y capturar salida
// 	char *result = process_backtick_substitution(buf, env);
// 	if (result != NULL)
// 	{
// 		if (ft_putstr(result, &(*token)->token) == -1)
// 		{
// 			free(buf);
// 			free(result);
// 			return; // Error de memoria
// 		}
// 		free(result);
// 	}
// 	free(buf);
	
// }
char *del_next_dquote(const char *var)
{
    if (var == NULL)
        return NULL;

    // Calcular la longitud de la cadena original
    size_t len = ft_strlen(var);
    char *result = malloc(len); // Reservar memoria para la nueva cadena
    if (!result)
        return NULL; // Manejo de error de memoria

    const char *src = var;
    char *dst = result;

    // Recorrer la cadena original
    while (*src)
    {
        if (*src == '\"') // Si encontramos el siguiente '"', lo omitimos
        {
            src++; // Saltar el carácter '"'
            continue;
        }
        *dst = *src; // Copiar el carácter actual
        dst++;
        src++;
    }
    *dst = '\0'; // Terminar la cadena resultante

    return result;
}

void case_dquote(char **line, t_token **token, t_env *env)
{
	(*line)++;
	(*token)->lit = 1;
	// SI CIERRA LA DOBLE COMILLA
	// Se interpreta lo de dentro literal
	if (ft_strnstr(*line, "\"",ft_strlen(*line)) != NULL)
	{
		while (**line != '\"')
		{
			// if (**line == '\\')
			// 	case_backlash(line, token);
			if (**line == '$')
			{
				case_dollar(line, token, env);
			}
			// if (**line == '`')
			// 	case_backtick(line, token, env);
			else
				ft_putchar(**line, &(*token)->token);
			(*line)++;
		}
	}
	else
		ft_putchar('\"', &(*token)->token);
	// COMILLA NO CERRADA
	// Espera mas inputs
	// else
	// {
	// 	while (ft_strnstr(*line, "\"",ft_strlen(*line)) == NULL && **line != '\"')
	// 	{
	// 		if (**line == '\\')
	// 			case_backlash(line, token);
	// 		if (**line == '$')
	// 			case_dollar(line, token, env);
	// 		if (**line == '`')
	// 			case_backtick(line, token, env);
	// 		else
	// 			ft_putchar(**line, &(*token)->token);
	// 		if (**line != '\0')
	// 			(*line)++;
	// 		else
	// 		{
	// 			*line = read_line(E_PROMPT_DQUOTE);
	// 		}
	// 	}
	// 	// while (ft_strnstr(*line, "\"",ft_strlen(*line)) == NULL)
	// 	// {
	// 	// 	// Concatenar a la linea anterior
	// 	// 	ft_putstr(*line, &(*token)->token);
	// 	// }
	// }
}

void case_dollar(char **line, t_token **token, t_env *env)
{
	char *var;
	char *value;

	if (*(*line + 1) == '\"')
	{
		ft_putchar('$', &(*token)->token);
		// ft_putchar('\"', &(*token)->token);
		// (*line)++;
		return;
	}
	(*line)++;
	// if (**line == '(')
	// {
	// 	// Ejecutar el comando dentro de $()
	// 	(*line)++;
	// 	// Guardar el comando en un buffer temporal
	// 	var = NULL;
	// 	while (**line != ')' && **line != '\0')
	// 	{
	// 		if (ft_putchar(**line, &var) == -1)
	// 		{
	// 			free(var);
	// 			return; // Error de memoria
	// 		}
	// 		(*line)++;
	// 	}
	// 	if (**line == ')')
	// 		(*line)++;
		
	// 	// Ejecutar el comando y capturar su salida
	// 	value = process_command_substitution(var, env);
	// 	if (value != NULL)
	// 	{
	// 		if (ft_putstr(value, &(*token)->token) == -1)
	// 		{
	// 			free(var);
	// 			free(value);
	// 			return; // Error de memoria
	// 		}
	// 		free(value);
	// 	}
	// 	free(var);
	// 	return ;
	// }
	if (**line == '\'')
	{
		ft_putchar('$', &(*token)->token);
		ft_putchar(**line, &(*token)->token);
		return;
	}
	if (**line == '?')
	{
		// Dejar $? sin expandir para expansión tardía
		if (ft_putstr(ft_itoa(g_last_exit_status), &(*token)->token) == -1)
			return; // Error de memoria
		// (*line)++;
		return ;
	}
	// Variables posicionales: $0, $1, $2, etc.
	if (**line >= '0' && **line <= '9')
	{
		if (**line == '0')
		{
			// $0 es el nombre del programa
			if (ft_putstr("minishell", &(*token)->token) == -1)
				return;
		}
		// $1, $2, etc. están vacíos (no hay argumentos en minishell)
		// No añadimos nada al token
		return;
	}
	// Obtener el nombre de la variable
	var = NULL;
	while (*(*line + 1) != ' ' && *(*line + 1) != '\t' && *(*line + 1) != '\0' && 
		   *(*line + 1) != '\'' && *(*line + 1) != '$')
	{
		if (((*token)->lit == 1 && *(*line + 1) == '\"'))
			break;
		ft_putchar(**line, &var);
		(*line)++;
	}
	ft_putchar(**line, &var);
	// var = del_next_dquote(var);
	if (var == NULL)
	{
		ft_putchar('$', &(*token)->token);
		return;
	}
	// Buscar el valor de la variable en las variables de entorno
	value = search_env_var(var, env);
	if (value != NULL)
	{
		if (ft_putstr(value, &(*token)->token) == -1)
		{
			if (ft_strnstr(*line, "\"",ft_strlen(*line)) != NULL && **line == '\'')
				ft_putchar('\'', &(*token)->token);
			free(var);
			return; // Error de memoria
		}
	}
	free(var);
}

int quoting(char **line, t_token **token, t_env *env)
{
	// if (**line == '\\')
	// {
	// 	case_backlash(line, token); 
	// 	return (TRUE);
	// }
	if (**line == '\'')
	{
		case_squote(line, token);
		return (TRUE);
	}
	else if (**line == '\"')
	{
		case_dquote(line, token, env);
		return (TRUE);
	}
	else if (**line == '$')
	{
		case_dollar(line, token, env);
		return (TRUE);
	}
	// else if (**line == '`')
	// {
	// 	case_backtick(line, token, env);
	// 	return (TRUE);
	// }
	else
		return (FALSE);
}