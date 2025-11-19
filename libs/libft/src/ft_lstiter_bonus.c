/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstiter_bonus.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/30 19:39:19 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/04/02 11:39:08 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/*  Iterates the list 'lst' and applies the function 'f' on the content of 
each node.*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f != NULL)
	{
		while (lst != NULL)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}

/*int main(void)
{
	t_list *lista;
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
	printf("Imprimimos lista:\n");
   
	ft_lstiter(lista, ft_print_content);
	ft_lstadd_front(&lista, aux2);
	ft_print_lst(&lista); 
	return (1);
} */