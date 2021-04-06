#include "minishell.h"

int		array_len(char **a)
{
	int i;

	i = 0;
	if (a)
		while (a[i])
			i++;
	return (i);
}

int		cmp_unsetval(char *s1, char *s2)
{
	int		i;
	char	*s;

	i = 0;
	while (s1[i] != '=' && s1[i] != '\0')
		i++;
	if (!(s = ft_substr(s1, 0, i)))
		return (0);
	if (ft_strlen(s) == ft_strlen(s2) && ft_strncmp(s, s2, ft_strlen(s)) == 0)
	{
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

t_list	*unset_env(t_list *env, char *searched)
{
	t_list	*env_cp;
	t_list	*env_next_cp;

	env_cp = env;
	if (cmp_unsetval(env_cp->content, searched))
	{
		env = env->next;
		ft_lstdelone(env_cp, free);
		return (env);
	}
	env_next_cp = env_cp->next;
	while (env_next_cp != NULL)
	{
		if (cmp_unsetval(env_next_cp->content, searched))
		{
			env_cp->next = env_next_cp->next;
            if (!env_next_cp)
	        	return (NULL);
            if (env_next_cp)
    	        free(env_next_cp);
			return (env);
		}
		env_cp = env_next_cp;
		env_next_cp = env_next_cp->next;
	}
	return (env);
}

int		check_unset_builtin(char *builtin)
{
	if ((builtin[0] >= 65 && builtin[0] <= 90) || (builtin[0] >= 97 && builtin[0] <= 122)
	|| builtin[0] == 95)
		return (1);
	return (0);
}

void	builtin_unset(char **builtin, t_list *env)
{
	int	i;
	int j;

	i = 1;
	if (array_len(builtin) == 1)
		return;
	if ((j = check_unset_builtin(builtin[i])) > 0)
	{
		while (builtin[i] != NULL)
			env = unset_env(env, builtin[i++]);
	}
	if (j == 0)
		printf("erreur\n");
}
