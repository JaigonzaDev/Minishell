/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:07:18 by mergarci          #+#    #+#             */
/*   Updated: 2025/07/16 13:10:20 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# ifndef MAX_NUM_FD
#  define MAX_NUM_FD 4096
# endif

typedef struct data
{
	char	*str_out;
	bool	found_n;
}	t_data;

// GNL
void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
char	*ft_read_gnl(int fd, t_data data, char **str_aux, ssize_t read_bytes);
char	*ft_gnl(int fd, char *limit);

//GNL_UTILS
char	*ft_substr_gnl(char const *s, unsigned int star, size_t len);
bool	ft_strchr_gnl(char **s, char **dst, int c);

#endif