/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_sort.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:58:30 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/05 16:58:33 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		export_display(char **env_tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env_tab[i])
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (env_tab[i][j] && env_tab[i][j] != '=')
		{
			ft_putchar_fd(env_tab[i][j], 1);
			j++;
		}
		if (env_tab[i][j] && env_tab[i][j] == '=')
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(env_tab[i] + j + 1, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void		export_sort_env(t_list *env)
{
	char	**env_tab;
	char	*env_tmp;
	int		i;
	int		j;

	env_tab = NULL;
	env_tab = lst_to_array(env);
	i = 0;
	while (env_tab[i])
	{
		j = i + 1;
		while (env_tab[j])
		{
			if (ft_strncmp(env_tab[i], env_tab[j], ft_strlen(env_tab[i])) > 0)
			{
				env_tmp = env_tab[i];
				env_tab[i] = env_tab[j];
				env_tab[j] = env_tmp;
			}
			j++;
		}
		i++;
	}
	export_display(env_tab);
	free(env_tab);
}
