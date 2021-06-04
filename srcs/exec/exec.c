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

static int	ft_exec(t_cmd *cmd, t_list *env, int tmp[2])
{
	if (is_built_in(cmd->cmd[0]))
		exec_built_in(cmd->cmd, env);
	else
	{
		g_pid = fork();
		if (g_pid < 0)
			error(FRK_ERR);
		else if (!g_pid)
		{
			if (get_absolute_path(cmd->cmd, env))
			{
				if (execve(cmd->cmd[0], cmd->cmd, lst_to_array(env)))
					print_error(cmd->cmd[0], CMD_ERR);
			}
			else
			{
				dup2(tmp[WRITE], WRITE);
				print_error(cmd->cmd[0], CMD_ERR);
				close(tmp[WRITE]);
				cmd->err = 127;
				return (-1);
			}
		}
	}
	return (0);
}

static void	end_exec(t_cmd *cmd, int tmp[2], int status)
{
	dup2(tmp[READ], READ);
	dup2(tmp[WRITE], WRITE);
	close(tmp[READ]);
	close(tmp[WRITE]);
	waitpid(g_pid, &status, 0);
	if (WIFEXITED(status))
		cmd->err = WEXITSTATUS(status);
}

static int	exec_cmd(t_list **cmds, t_list *env, t_list *hist)
{
	int		tmp[2];
	int		fd[2];
	int		fdpipe[2];
	int		status;
	t_cmd	*cmd;

	cmd = (t_cmd *)(*cmds)->content;
	tmp[READ] = dup(READ);
	tmp[WRITE] = dup(WRITE);
	status = 0;
	fd[READ] = get_fd(cmd, 0, tmp[READ], READ);
	if (fd[READ] == -1)
		return (-1);
	while (42)
	{
		cmd = (t_cmd *)(*cmds)->content;
		if (open_close_fds(cmd, fd, tmp, fdpipe))
			return (-1);
		if (ft_exec(cmd, env, tmp))
			ft_exit(*cmds, env, hist, cmd->err);
		if (!cmd->nb)
			break ;
		*cmds = (*cmds)->next;
	}
	end_exec(cmd, tmp, status);
	return (cmd->err);
}

int	exec_cmds(t_params *params, int ret)
{
	t_cmd	*cmd;

	cmd = NULL;
	while (params->cmds)
	{
		if (cmd && cmd->err)
			ret = cmd->err;
		cmd = (t_cmd *)params->cmds->content;
		cmd->err = ret;
		replace_in_cmd(cmd, "\'\"", params->env);
		if (cmd->cmd[0])
			ret = exec_cmd(&params->cmds, params->env, params->hist);
		params->cmds = params->cmds->next;
	}
	return (ret);
}
