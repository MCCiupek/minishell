/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:51:35 by mciupek           #+#    #+#             */
/*   Updated: 2021/05/12 16:51:38 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	clear_lsts(t_list *c, t_list *env, t_list *hist)
{
	if (c)
		ft_lstclear(&c, free_t_cmd);
	if (env)
		ft_lstclear(&env, free);
	if (hist)
		ft_lstclear(&hist, free);
	term_off();
}

void	set_error_msg(char *s)
{
	char	*msg;

	msg = ft_strjoin("exit: ", s);
	print_error(msg, EXIT_NUM);
	free(msg);
}

void	ft_exit(t_list *c, t_list *env, t_list *hist)
{
	t_cmd	*cmd;

	if (c)
	{
		cmd = (t_cmd *)c->content;
		if (cmd && !ft_strncmp(cmd->cmd[0], "exit", 4)
			&& array_len(cmd->cmd) > 1)
		{
			if (!str_isdigit(cmd->cmd[1]))
				set_error_msg(cmd->cmd[1]);
			else if (array_len(cmd->cmd) > 2)
			{
				print_error("exit", EXIT_NARG);
				term_off();
				return ;
			}
			g_gbl.exit = ft_atoi(cmd->cmd[1]);
		}
	}
	clear_lsts(c, env, hist);
	exit(g_gbl.exit);
}

void	builtin_exit(t_list *c, t_list *env, t_list *hist)
{
	ft_putstr_fd("exit\n", STDERROR);
	ft_exit(c, env, hist);
}
