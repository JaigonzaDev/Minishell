/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mergarci <mergarci@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/25 11:44:20 by mergarci		  #+#	#+#			 */
/*   Updated: 2024/03/25 11:44:20 by mergarci		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

/*Removes all characters from the string 'set' from the beginning and end 
of 's1', until a character not belonging to 'set' is found. The resulting 
string is returned with a malloc(3) fallback.*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_s1;
	size_t	ini;
	size_t	end;
	char	*aux;

	len_s1 = ft_strlen(s1);
	if (len_s1 == 0)
		return (ft_strdup(""));
	ini = 0;
	end = len_s1 - 1;
	aux = ft_strrchr(set, s1[ini]);
	while (ini < len_s1 && aux != NULL)
		aux = ft_strrchr(set, s1[ini++]);
	if (ini != 0)
		ini--;
	aux = ft_strrchr(set, s1[end--]);
	while (end > 0 && aux != NULL)
		aux = ft_strrchr(set, s1[end--]);
	if (end == 0)
		end = ini;
	else
		end++;
	if (len_s1 == 0 || (ini == len_s1 - 1 && end == len_s1 - 1))
		return (ft_strdup(""));
	return (ft_substr(s1, (unsigned int)ini, end - ini + 1));
}
/*
int main()
{
	char *str = "";
	char *set = "";
	char *new = ft_strtrim(str, set);
	//dst = ft_strjoin(str, dst);
	printf("|%s|", new);

	return 0;
}*/