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
# include <stdlib.h>

typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

void	env_save(char **envp, t_env **my_environment);
t_env	*env_free(t_env *env);
void	env_freeall(t_env **env);
void	env_save_simple(char **envp);
void	env_print_simple(void);
void	env_free_simple(void);
char	*env_get_simple(const char *name);

/* environment_utils.c */
void	allocate_var_content(t_env *var, char *str, char *equal_pos);

#endif