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

static int	ft_exec(t_cmd *cmd, t_list *env)
{
	char	**tab;

	if (is_built_in(cmd->cmd[0]))
		return (cmd->err = exec_built_in(cmd->cmd, env));
	else
	{
		g_pid = fork();
		if (g_pid < 0)
			error(FRK_ERR);
		else if (!g_pid)
		{
			if (get_absolute_path(cmd->cmd, env))
			{
				tab = lst_to_array(env);
				if (execve(cmd->cmd[0], cmd->cmd, tab))
				{
					print_error(cmd->cmd[0], ERRNO_TO_STR);
					cmd->err = 126;
					tab = free_array(tab);
					return (-1);
				}
			}
			else
			{
				print_error(cmd->cmd[0], CMD_ERR);
				cmd->err = 127;
				return (-1);
			}
		}
	}
	return (0);
}

static void	end_exec(t_cmd *cmd, int tmp[2], int status, int ret)
{
	dup2(tmp[READ], READ);
	dup2(tmp[WRITE], WRITE);
	close(tmp[READ]);
	close(tmp[WRITE]);
	waitpid(g_pid, &status, 0);
	if (WIFEXITED(status) && ret != 1)
		cmd->err = WEXITSTATUS(status);
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
	int		fd[2];
	int		fdpipe[2];
	int		status[2];
	t_cmd	*cmd;

	cmd = (t_cmd *)(*cmds)->content;
	start_exec(tmp, &status[0]);
	fd[READ] = get_fd(cmd, 0, tmp[READ], READ);
	if (fd[READ] == -1)
		return (-1);
	while (42)
	{
		cmd = (t_cmd *)(*cmds)->content;
		if (open_close_fds(cmd, fd, tmp, fdpipe))
			return (-1);
		status[1] = ft_exec(cmd, env);
		if (status[1] == -1)
		{
			free(line);
			ft_exit(*cmds, env, hist, cmd->err);
		}
		if (!cmd->nb)
			break ;
		*cmds = (*cmds)->next;
	}
	end_exec(cmd, tmp, status[0], status[1]);
	return (cmd->err);
}

int	exec_cmds(t_params *params, int ret, char *line)
{
	t_cmd	*cmd;
	t_list	*tmp;

	cmd = NULL;
	tmp = params->cmds;
	while (tmp)
	{
		if (cmd && cmd->err)
			ret = cmd->err;
		cmd = (t_cmd *)tmp->content;
		cmd->err = ret;
		replace_in_cmd(cmd, "\'\"", params->env);
		if (cmd->cmd[0])
			ret = exec_cmd(&tmp, params->env, params->hist, line);
		tmp = tmp->next;
	}
	return (ret);
}
