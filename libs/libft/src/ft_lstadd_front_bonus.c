/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstadd_front_bonus.c							:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/27 13:05:33 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/04/02 11:36:23 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Add the 'new' node to the beginning of the 'lst' list. */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (*lst != NULL)
		new->next = *lst;
	*lst = new;
}

/*int main(void)
{
	t_list *lista;
	t_list *new;
	lista = ft_calloc(2, sizeof(t_list));
	lista = ft_lstnew("hola");
	new = ft_lstnew(("adios"));
	printf("Imprimimos lista:\n");
	ft_print_lst(&lista);
	printf("Imprimimos new:\n");
	ft_print_lst(&new);  
	ft_lstadd_front(&lista, new);
	printf("Imprimimos lista:\n");
	ft_print_lst(&lista); 

	return (1);
}*/