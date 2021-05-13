/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:21:16 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/13 16:21:17 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd",
		"env", "exit", "unset", "export", "echo", NULL};
	int			i;

	i = 0;
	if (!cmd)
		return (0);
	while (built_in[i])
	{
		if (!ft_strncmp(cmd, built_in[i], ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}

void	exec_built_in(char **built_in, t_list *env)
{
	if (!ft_strncmp(built_in[0], "pwd", 3))
		built_in_pwd();
	else if (!ft_strncmp(built_in[0], "cd", 2))
		built_in_cd_nbargs(built_in, env);
	else if (!ft_strncmp(built_in[0], "env", 3))
		built_in_env(env);
	else if (!ft_strncmp(built_in[0], "echo", 4))
		built_in_echo(built_in, env);
	else if (!ft_strncmp(built_in[0], "unset", 4))
		builtin_unset(built_in, env);
	else if (!ft_strncmp(built_in[0], "export", 6))
		builtin_export(built_in, env);
}
