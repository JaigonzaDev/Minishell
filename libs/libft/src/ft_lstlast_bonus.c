/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstlast_bonus.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/28 18:56:36 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/04/02 11:41:18 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Returns the last node in the list. */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*aux;

	aux = lst;
	while (aux)
	{
		if (aux->next == NULL)
			return (aux);
		aux = aux->next;
	}
	return (aux);
}

/*int main(void)
{
	t_list *lista;
	t_list *new;
	t_list *aux;
	t_list *last;
	lista = ft_calloc(2, sizeof(t_list));
	lista = ft_lstnew("hola");
	new = ft_lstnew(("adios"));
	aux = ft_lstnew(("que tal estais?"));
	ft_lstadd_front(&lista, new);
	ft_lstadd_front(&lista, aux);
	printf("Imprimimos lista:\n");
	ft_print_lst(&lista); 
	printf("numeros de elementos en la lista: %d\n", ft_lstsize(lista));
	printf("ultimo nodo:\n");
	last = ft_lstlast(lista);
	ft_print_lst(&last);
	return (1);
} */