/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:06:24 by mergarci          #+#    #+#             */
/*   Updated: 2025/07/16 13:17:12 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			cont;

	cont = 0;
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	while (cont < size)
		ptr[cont++] = '\0';
	return ((void *)ptr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;
	int		i;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	ptr = (char *)ft_calloc_gnl(len_s1 + len_s2 + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (len_s1--)
	{
		ptr[i] = s1[i];
		i++;
	}
	len_s1 = i;
	i = 0;
	while (len_s2--)
		ptr[len_s1++] = s2[i++];
	ptr[len_s1] = '\0';
	return (ptr);
}

char	*ft_read_gnl(int fd, t_data data, char **str_aux, ssize_t read_bytes)
{
	char		*ptr_aux;
	char		*buffer;

	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (read_bytes > 0 && !data.found_n)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buffer[read_bytes] = '\0';
		data.found_n = ft_strchr_gnl(&buffer, str_aux, '\n');
		ptr_aux = data.str_out;
		data.str_out = ft_strjoin_gnl(data.str_out, buffer);
		ptr_aux = ft_memfree(ptr_aux);
	}
	buffer = ft_memfree(buffer);
	if ((read_bytes == 0 && ft_strlen(data.str_out) == 0) || read_bytes < 0)
	{
		*str_aux = ft_memfree(*str_aux);
		data.str_out = ft_memfree(data.str_out);
	}
	return (data.str_out);
}

char	*ft_gnl(int fd, char *limit)
{
	static char	*str_aux[MAX_NUM_FD];
	t_data		data;
	ssize_t		read_bytes;

	data.found_n = false;
	read_bytes = 1;
	if (fd == -10 && limit == NULL)
	{
		str_aux[fd] = ft_memfree(str_aux[fd]);
		return (NULL);
	}
	if (fd == -1 || BUFFER_SIZE == 0)
		return (NULL);
	data.str_out = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!data.str_out)
		return (NULL);
	if (!str_aux[fd])
		str_aux[fd] = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	else
	{
		ft_strlcpy(data.str_out, str_aux[fd], ft_strlen(str_aux[fd]) + 1);
		data.found_n = ft_strchr_gnl(&data.str_out, &str_aux[fd], '\n');
	}
	data.str_out = ft_read_gnl(fd, data, &str_aux[fd], read_bytes);
	return (data.str_out);
}

/*int	main(void)
{
	int		fd1;
	int		fd2;
	char	*aux;

	fd1 = open("test1.txt", O_RDWR);
	fd2 = open("test.txt", O_RDWR);
	//fd = 10000;
 	if (fd1 != -1 && fd2 != 2)
	{
		aux = get_next_line(fd1);
		while (aux != NULL)
		{
			printf("%s", aux);
			free(aux);
			aux = get_next_line(fd2);
			printf("%s", aux);
			free(aux);
			aux = get_next_line(fd1);
		}
		free(aux);
	} 
	close(fd1);
	close(fd2);
	return (1);
}*/
