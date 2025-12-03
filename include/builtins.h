/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaigonza <jaigonza@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:29:22 by jaigonza          #+#    #+#             */
/*   Updated: 2025/12/03 08:29:26 by jaigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"
# include "ft_printf.h"
# include <stdbool.h>
# include <stdio.h>

int		ft_cd(char *path, t_env **environment);
void	ft_echo(char **args);
void	ft_env(t_env *enviroment);
void	ft_exit(char **args, t_env **environment);
int		ft_export(char **args, t_env **environment);
void	ft_pwd(void);
void	ft_unset(char *var, t_env **enviroment);
bool	ft_is_builtin(char *command);
int		ft_execute_builtin(char **args, t_env **environment);
int		ft_true(void);
int		ft_false(void);

/* export_utils.c */
int		is_valid_identifier(const char *str);
char	*extract_var_name(const char *arg);
char	*extract_var_value(const char *arg);
t_env	*create_env_node(char *key, char *value);
int		update_existing_env(t_env *env, char *key, char *value);

#endif