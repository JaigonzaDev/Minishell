/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mergarci <mergarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 12:55:05 by mergarci          #+#    #+#             */
/*   Updated: 2024/04/15 13:45:04 by mergarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* It takes as a parameter a node 'lst' and frees the memory of the content 
using the function 'del' given as a parameter, in addition to freeing the 
node. The 'next' memory must not be freed. */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	(del)(lst->content);
	free(lst);
}

/*int main(void)
{
	t_list *lista;
	t_list *new;
	t_list *aux;

	lista = ft_calloc(2, sizeof(t_list));
	lista = ft_lstnew("hola");
	new = ft_lstnew(("adios"));
	aux = ft_lstnew(("que tal estais?"));
	ft_lstdealone(new, ft_del);
	ft_lstadd_front(&lista, new);
	ft_lstadd_back(&lista, aux);
	printf("Imprimimos lista:\n");
	ft_print_lst(&lista); 
	
	//printf("Imprimimos lista:\n");
	//ft_print_lst(&lista); 

	return (1);
} */