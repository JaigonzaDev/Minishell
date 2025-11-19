/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstclear_bonus.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/29 12:33:15 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/04/02 11:37:57 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Delete and free the given ’lst’ node and all consecutive nodes of that 
node, using the ’del’ and free(3) function.
In the end, the pointer to the list must be NULL. */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (lst)
	{
		while (*lst != NULL)
		{
			aux = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = aux;
		}
	}
}
/*
int main(void)
{
	t_list *lista;
	t_list *new;
	t_list *aux;

	lista = ft_calloc(2, sizeof(t_list));
	lista = ft_lstnew("hola");
	new = ft_lstnew(("adios"));
	aux = ft_lstnew(("que tal estais?"));
	//ft_lstdealone(new, ft_del);
	ft_lstadd_front(&lista, new);
	ft_lstadd_back(&lista, aux);
	printf("Imprimimos lista!!!:\n");
	ft_print_lst(&lista); 
	printf("Borramos lista!!!:\n");
	ft_lstclear(&lista, ft_del);
	printf("%p\n", &lista);
	printf("Imprimimos lista despues de borrado:\n");
	ft_print_lst(&lista); 

	return (1);
}*/