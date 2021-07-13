/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:27:57 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:27:59 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec(t_cmd *cmd, t_list *env)
{
	if (is_built_in(cmd->cmd[0]))
		return (g_gbl.exit = exec_built_in(cmd->cmd, env));
	else
	{
		g_gbl.pid = fork();
		if (g_gbl.pid < 0)
			error(FRK_ERR);
		else if (!g_gbl.pid)
			return (ft_child(cmd, env));
		else if (g_gbl.pid > 0)
			ft_parent(cmd);
		if (cmd->nb_pipes > 1)
		{
			close(cmd->fd[READ]);
			close(cmd->fd[WRITE]);
		}
	}
	return (0);
}

static void	end_exec(int tmp[2], int status)
{
	dup2(tmp[READ], STDIN);
	dup2(tmp[WRITE], STDOUT);
	close(tmp[READ]);
	close(tmp[WRITE]);
	waitpid(g_gbl.pid, &status, 0);
	if (WIFEXITED(status) && !g_gbl.exit)
		g_gbl.exit = WEXITSTATUS(status);
}

static void	start_exec(int tmp[2], int *status)
{
	tmp[READ] = dup(READ);
	tmp[WRITE] = dup(WRITE);
	*status = 0;
}

static int	exec_cmd(t_list **cmds, t_list *env, t_list *hist, char *line)
{
	int		tmp[2];
	int		status;
	t_cmd	*cmd;

	cmd = (t_cmd *)(*cmds)->content;
	start_exec(tmp, &status);
	cmd->fd[READ] = get_fd(cmd, 0, tmp[READ], READ);
	if (cmd->fd[READ] == -1)
		return (g_gbl.exit = -1);
	cmd->fd[WRITE] = open_close_fds(cmd, cmd->fd, tmp);
	if (cmd->fd[WRITE])
		return (g_gbl.exit = -1);
	if (ft_exec(cmd, env) == -1)
	{
		free(line);
		ft_exit(*cmds, env, hist);
	}
	end_exec(tmp, status);
	return (0);
}

int	exec_cmds(t_params *params, char *line)
{
	t_cmd	*cmd;
	t_list	*tmp;

	cmd = NULL;
	tmp = params->cmds;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		replace_in_cmd(cmd, "\'\"");
		reparse_cmd(cmd);
		if (cmd->nb_pipes == 1)
			exec_cmd(&tmp, params->env, params->hist, line);
		if (cmd->nb_pipes > 1)
			ft_pipe(&tmp, params, line);
		tmp = tmp->next;
	}
	return (0);
}
