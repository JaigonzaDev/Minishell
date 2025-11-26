#include "minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2))
    {
        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

char *search_env_var(char *key, t_env *env)
{
    t_env *tmp;

    tmp = env;

    while (tmp)
    {
        // Verificar si el nombre de la variable coincide exactamente
        if (ft_strcmp(tmp->var, key) == 0)
            return (tmp->content);
        tmp = tmp->next;
    }
    return (NULL);
}
