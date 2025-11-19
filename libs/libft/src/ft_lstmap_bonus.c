/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstmap_bonus.c								  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/30 20:02:20 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/04/02 11:42:33 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* 
Iterates the list 'lst' and applies the function 'f' to the contents of each
node. Creates a list resulting from the correct and successive application of
the function 'f' on each node. The 'del' function is used to delete the 
contents of a node, if necessary. */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*aux;
	void	*new_content;

	if (lst != NULL && f != NULL && del != NULL)
	{
		list = NULL;
		while (lst != NULL)
		{
			new_content = f(lst->content);
			aux = ft_lstnew(new_content);
			if (!aux)
			{
				(del)(new_content);
				ft_lstclear(&list, del);
				return (NULL);
			}
			ft_lstadd_back(&list, aux);
			lst = lst->next;
		}
		return (list);
	}
	return (NULL);
}

/* int main(void)
{
	t_list *lista;
	t_list *lista2;
	t_list *new;
	t_list *aux;
	t_list *aux2;
	lista = ft_calloc(2, sizeof(t_list));
	lista = ft_lstnew("hola");
	new = ft_lstnew(("adios"));
	aux = ft_lstnew(("que tal estais?"));
	aux2 = ft_lstnew(("soy MGM"));
	//ft_lstdealone(new, ft_del);
	ft_lstadd_front(&lista, new);
	ft_lstadd_back(&lista, aux);
	printf("***************Imprimimos lista:\n");
   
	//ft_lstiter(lista, ft_print_content);
	ft_lstadd_front(&lista, aux2);
	ft_print_lst(&lista); 
	printf("***************Imprimimos lista2:\n");
	lista2 = ft_lstmap(lista, ft_strtoupper, ft_del);
	ft_print_lst(&lista2); 
	return (1);
}   */