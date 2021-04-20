/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:37:36 by fcivetta          #+#    #+#             */
/*   Updated: 2021/03/25 17:41:15 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_envvar(char *s, t_list *env)
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

void		echo_env(char *s, t_list *env)
{
	if (s[1] == '$')
		printf("trouver la valeur de $$ à afficher\n");
	else
		print_envvar(s, env);
}

void		built_in_echo(char **cmd, t_list *env)
{
	int		new_line;
	int		i;

	i = 1;
	new_line = 1;
	(void)env;
	if (cmd[1] && !ft_strncmp(cmd[i], "-n", 3))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		if (cmd[i][0] == '$' && cmd[i][1])
			echo_env(cmd[i], env);
		else
			ft_putstr_fd(cmd[i], 1);
		i++;
		if (cmd[i])
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
}
