/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/27 14:56:36 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/04/02 11:35:25 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/* Convert ASCII string to integer */
int	ft_atoi(const char *str)
{
	int	i;
	int	is_negative;
	int	result;

	i = 0;
	is_negative = 0;
	result = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			is_negative = 1;
	}
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			break ;
		result = result * 10 + str[i] - '0';
		i++;
	}
	if (is_negative)
		result = -result;
	return (result);
}

/*int main(void)
{
	char str[] = " -1234ab567";
	printf("Resultado de \"%s\" con la funcion atoi: %d\n", str, atoi(str));
	printf("Resultado de \"%s\" con la func ft_atoi: %d\n", str, ft_atoi(str));
	
	return (0);
}*/
