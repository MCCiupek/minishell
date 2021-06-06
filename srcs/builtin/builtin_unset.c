/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 22:32:58 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/05 22:33:00 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_len(char **a)
{
	int	i;

	i = 0;
	if (a)
		while (a[i])
			i++;
	return (i);
}

int	cmp_unsetval(char *s1, char *s2)
{
	int		i;
	char	*s;

	i = 0;
	if (!s1)
		return (0);
	while (s1[i] != '=' && s1[i] != '\0')
		i++;
	s = ft_substr(s1, 0, i);
	if (!s)
		return (0);
	if (ft_strlen(s) == ft_strlen(s2) && ft_strncmp(s, s2, ft_strlen(s)) == 0)
	{
		free(s);
		return (1);
	}
	free(s);
	return (0);
}

t_list	*unset_val(t_list **env, t_list	*env_cp)
{
	*env = (*env)->next;
	ft_lstdelone(env_cp, free);
	return (*env);
}

t_list	*unset_env(t_list **env, char *searched)
{
	t_list	*env_cp;
	t_list	*env_next_cp;

	env_cp = *env;
	if (cmp_unsetval(env_cp->content, searched))
		return (unset_val(env, env_cp));
	env_next_cp = env_cp->next;
	while (env_next_cp)
	{
		if (cmp_unsetval(env_next_cp->content, searched))
		{
			env_cp->next = env_next_cp->next;
			if (!env_next_cp)
				return (NULL);
			if (env_next_cp)
				ft_lstdelone(env_next_cp, free);
			return (*env);
		}
		env_cp = env_next_cp;
		env_next_cp = env_next_cp->next;
	}
	return (*env);
}

int	check_unset_builtin(char *builtin)
{
	if ((builtin[0] >= 65 && builtin[0] <= 90)
		|| (builtin[0] >= 97 && builtin[0] <= 122)
		|| builtin[0] == 95)
		return (1);
	return (0);
}

void	builtin_unset(char **builtin, t_list **env)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 1;
	tmp = NULL;
	if (array_len(builtin) == 1)
		return ;
	j = check_unset_builtin(builtin[i]);
	if (j > 0)
	{
		while (builtin[i] != NULL)
		{
			tmp = *env;
			unset_env(env, builtin[i++]);
		}
	}
	if (j == 0)
	{
		ft_putstr_fd("minishell: unset: « ", STDERROR);
		ft_putstr_fd(builtin[i], STDERROR);
		ft_putstr_fd(" » : identifiant non valable\n", STDERROR);
	}
}
