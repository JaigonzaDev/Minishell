/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 15:58:17 by mergarci          #+#    #+#             */
/*   Updated: 2025/08/30 18:51:16 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "../libs/libft/include/ft_printf.h"

typedef struct s_env
{
    char    *var;
    char    *content;
    struct s_env *next;
} t_env;


//environment.c
void env_save(char **envp, t_env **myEnvironment);
t_env *env_free(t_env *env);
void env_freeall(t_env **env);

// Funciones simples y seguras para environment
void env_save_simple(char **envp);
void env_print_simple(void);
void env_free_simple(void);
char *env_get_simple(const char *name);

#endif