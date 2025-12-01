/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:54:16 by mergarci          #+#    #+#             */
/*   Updated: 2025/08/30 18:00:35 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdio.h>
# include <stdbool.h>
# include "ft_printf.h"
# include "environment.h"

// Function prototypes for all builtins

//cd.c
int ft_cd(char *path, t_env **environment);

//echo.c
void ft_echo(char **args);

//env.c
void ft_env(t_env *enviroment);

//exit.c
void ft_exit(char **args, t_env **environment);

//export.c
int ft_export(char **args, t_env **environment);

//pwd.c
void ft_pwd(void);

//unset.c
void ft_unset(char *var, t_env **enviroment);

//builtins_utils.c
bool ft_is_builtin(char *command);
int ft_execute_builtin(char **args, t_env **environment);

//true_false.c
int ft_true(void);
int ft_false(void);


#endif