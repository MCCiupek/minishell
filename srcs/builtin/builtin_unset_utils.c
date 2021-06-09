/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:09:55 by lkonig            #+#    #+#             */
/*   Updated: 2021/06/09 14:10:03 by lkonig           ###   ########.fr       */
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

int	check_unset_builtin(char *builtin)
{
	if ((builtin[0] >= 65 && builtin[0] <= 90)
		|| (builtin[0] >= 97 && builtin[0] <= 122)
		|| builtin[0] == 95)
		return (1);
	return (0);
}
