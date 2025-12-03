/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cinaquiz <cinaquiz@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:31:49 by cinaquiz          #+#    #+#             */
/*   Updated: 2025/12/03 08:33:52 by cinaquiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Create a new node using malloc(3). The member variable 'content' is
initialized with the content of the parameter 'content'. The 'next' variable,
with NULL. */
t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

/*int main(void)
{
	t_list *lista;
	lista = ft_lstnew((void *)"hola");

	printf("%s", (char *)lista->content);

	return (1);
}*/