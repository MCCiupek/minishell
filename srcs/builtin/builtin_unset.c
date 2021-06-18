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

int	builtin_unset(char **builtin, t_list **env)
{
	int		i;
	int		j;
	t_list	*tmp;

	i = 1;
	tmp = NULL;
	if (array_len(builtin) == 1)
		return (1);
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
		ft_putstr_fd("minishell: unset: `", STDERROR);
		ft_putstr_fd(builtin[i], STDERROR);
		ft_putstr_fd("' : not a valid identifier\n", STDERROR);
		return (1);
	}
	return (0);
}
