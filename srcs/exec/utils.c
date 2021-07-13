/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:27:57 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:27:59 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_err(t_cmd *cmd, int exit, int err)
{
	print_error(cmd->cmd[0], err);
	g_gbl.exit = exit;
	return (-1);
}

int	ft_child(t_cmd *cmd, t_list *env)
{
	char	**tab;
	int		path;

	path = get_absolute_path(cmd->cmd, env);
	if (path == 1 && ft_strncmp(cmd->cmd[0], "..", 2))
	{
		tab = lst_to_array(env);
		if (execve(cmd->cmd[0], cmd->cmd, tab))
		{
			print_error(cmd->cmd[0], ERRNO_TO_STR);
			g_gbl.exit = 127;
			if (errno == 13)
				g_gbl.exit = 126;
			tab = free_array(tab);
			return (-1);
		}
	}
	else if (!path || !ft_strncmp(cmd->cmd[0], "..", 2))
		return (ft_err(cmd, 127, CMD_ERR));
	else if (path == -1)
		return (ft_err(cmd, 127, PATH_ERR));
	return (0);
}

int	ft_parent(t_cmd *cmd)
{
	wait(&g_gbl.exit);
	if (g_gbl.exit == SIGINT)
		g_gbl.exit = 130;
	else if (g_gbl.exit == SIGQUIT)
		g_gbl.exit = 131;
	else if (!is_built_in(cmd->cmd[0]))
		g_gbl.exit = WEXITSTATUS(g_gbl.exit);
	return (0);
}

int	reparse_cmd(t_cmd *cmd)
{
	char	**new_cmd;
	char	*tmp1;
	char	*tmp2;
	size_t	i;

	i = 0;
	tmp1 = ft_strjoin(cmd->cmd[i], " ");
	while (cmd->cmd[++i])
	{
		tmp2 = ft_strjoin(tmp1, cmd->cmd[i]);
		free(tmp1);
		tmp1 = ft_strjoin(tmp2, " ");
		free(tmp2);
	}
	new_cmd = tokenize(tmp1, " \t\n", NULL, 0);
	free_array(cmd->cmd);
	free(tmp1);
	cmd->cmd = new_cmd;
	return (0);
}
