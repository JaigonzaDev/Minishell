/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:17:15 by mergarci          #+#    #+#             */
/*   Updated: 2025/05/03 19:40:24 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include "libft.h"
# include <stdlib.h>

# include <limits.h>
# include <stdbool.h>

# ifndef HEX
#  define HEX "0123456789abcdef"
# endif

//ft_printf.c
int		ft_printf(char const *s, ...);
int		ft_check_placeholder(char const *s, int *i, va_list vargs);
int		ft_placeholder_c(va_list vargs, char type);
int		ft_placeholder_s(va_list vargs);
int		ft_placeholder_p(va_list vargs);

//ft_printf_utils.c
int		ft_placeholder_d(va_list vargs);
int		ft_placeholder_u(va_list vargs);
int		ft_print_str(char *str);
//char	*ft_memfree(char *ptr);

//ft_printf_hex.c
int		ft_convert(long int nb, char type, int n_written);
int		ft_placeholder_hex(va_list vargs, char type);
#endif