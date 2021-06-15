/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:22:04 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/13 16:22:05 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_envvar(char *s, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, s + 1, ft_strlen(s) - 1) == 0)
		{
			ft_putstr_fd((char *)tmp->content + (ft_strlen(s)), 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	echo_env(char *s, t_list *env)
{
	print_envvar(s, env);
}

static int	is_n(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (0);
	while (s[i])
		if (s[i++] != 'n')
			return (0);
	return (1);
}

int	built_in_echo(char **cmd, t_list *env)
{
	int		new_line;
	int		i;

	i = 1;
	new_line = 1;
	(void)env;
	while (cmd[1] && is_n(cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
