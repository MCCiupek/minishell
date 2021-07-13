/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:27:57 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:27:59 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_parent_pipe(int fdpipe[2], t_list **cmds, t_params *params,
							char *line)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)(*cmds)->content;
	if (!ft_strncmp(cmd->cmd[0], "cat", 3) && !cmd->cmd[1] && cmd->in)
	{
		cmd->fd[READ] = get_fd(cmd, 0, fdpipe[0], READ);
		dup2(cmd->fd[READ], STDIN);
		close(cmd->fd[READ]);
	}
	close(fdpipe[0]);
	cmd->fd[WRITE] = get_fd(cmd, 0644, fdpipe[1], WRITE);
	dup2(cmd->fd[WRITE], STDOUT);
	if (ft_exec(cmd, params->env))
		g_gbl.exit = 127;
	close(fdpipe[1]);
	free(line);
	ft_exit(*cmds, params->env, params->hist);
	return (0);
}

static int	exec_pipe(int fdpipe[2], t_list **cmds, t_params *params,
							char *line)
{
	t_cmd	*cmd;

	if (g_gbl.pid > 0)
	{
		close(fdpipe[1]);
		*cmds = (*cmds)->next;
		cmd = (t_cmd *)(*cmds)->content;
		cmd->fd[READ] = get_fd(cmd, 0, fdpipe[0], READ);
		dup2(cmd->fd[READ], STDIN);
		close(fdpipe[0]);
	}
	else if (!g_gbl.pid)
		exec_parent_pipe(fdpipe, cmds, params, line);
	return (0);
}

static int	create_pipe(t_list **cmds, t_params *params,
							int *nb_wait, char *line)
{
	int		fdpipe[2];

	if (pipe(fdpipe) == -1)
	{
		ft_putstr_fd("pipe: pipe failed\n", STDERROR);
		return (-1);
	}
	(*nb_wait)++;
	g_gbl.pid = fork();
	if (g_gbl.pid < 0)
	{
		ft_putstr_fd("pipe: fork failed\n", STDERROR);
		return (-1);
	}
	else
		return (exec_pipe(fdpipe, cmds, params, line));
}

static int	final_pipe(t_list *cmds, t_params *params, int fd[2])
{
	t_cmd	*cmd;

	cmd = (t_cmd *)(cmds)->content;
	cmd->fd[WRITE] = get_fd(cmd, 0644, fd[1], WRITE);
	dup2(cmd->fd[WRITE], STDOUT);
	if (ft_exec(cmd, params->env))
	{
		reset_fds(fd);
		reset_fds(cmd->fd);
		if (g_gbl.exit > 1)
			ft_exit(cmds, params->env, params->hist);
	}
	return (g_gbl.exit);
}

int	ft_pipe(t_list **cmds, t_params *params, char *line)
{
	int		fd[2];
	int		nb_wait;
	int		ret;

	nb_wait = 0;
	init_fds(&fd[READ], &fd[WRITE]);
	init_fds(&((t_cmd *)(*cmds)->content)->fd[READ],
		&((t_cmd *)(*cmds)->content)->fd[WRITE]);
	while (cmds)
	{
		while (cmds && ((t_cmd *)(*cmds)->content)->nb)
		{
			ret = create_pipe(cmds, params, &nb_wait, line);
			if (ret)
				break ;
		}
		ret = final_pipe(*cmds, params, fd);
		reset_fds(fd);
		if (!((t_cmd *)(*cmds)->content)->nb)
			break ;
		*cmds = ft_lstnext(cmds);
	}
	ft_wait(nb_wait);
	return (g_gbl.exit = ret);
}
