#include "minishell.h"

char *search_env_var(char *key, t_env *env)
{
	t_env *tmp;

	tmp = env;

	while(env)
	{
		if (ft_strncmp(tmp->var, key, ft_strlen(key)) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
