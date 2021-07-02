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

static int	last_pipe_exit(t_list **cmds, int old_fdin)
{
	dup2(old_fdin, STDIN);
	*cmds = (*cmds)->next;
	return (42);
}

static int	create_pipe2(int fdpipe[2], t_list **cmds, t_list *env,
							int old_fdin)
{
	if (g_gbl.pid > 0)
	{
		close(fdpipe[1]);
		if (!((t_cmd *)(*cmds)->content)->nb)
			return (last_pipe_exit(cmds, old_fdin));
		*cmds = (*cmds)->next;
		((t_cmd *)(*cmds)->content)->fdin = fdpipe[0];
		dup2(((t_cmd *)(*cmds)->content)->fdin, STDIN);
		close(fdpipe[0]);
	}
	else if (!g_gbl.pid)
	{
		close(fdpipe[0]);
		((t_cmd *)(*cmds)->content)->fdout = fdpipe[1];
		dup2(((t_cmd *)(*cmds)->content)->fdout, STDOUT);
		if (ft_exec((t_cmd *)(*cmds)->content, env))
			g_gbl.exit = 127;
		close(fdpipe[1]);
		exit(0);
	}
	return (0);
}

int			create_pipe(t_list **cmds, t_list *env,
							int old_fdin, int *nb_wait)
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
		return (create_pipe2(fdpipe, cmds, env, old_fdin));
}

static int		function(t_list *cmds, t_list *env, int fd[2])
{
	if (ft_exec((t_cmd *)cmds->content, env))
	{
		reset_fds(fd);
		return (-1);
	}
	return (0);
}

int		ft_pipe(t_list **cmds, t_list *env)
{
	int	fd[2];
	int	nb_wait;
	int	ret;

	init_fds(&fd[READ], &fd[WRITE]);
	while (cmds)
	{
		while (cmds && ((t_cmd *)(*cmds)->content)->nb)
		{
			ret = create_pipe(cmds, env, fd[READ], &nb_wait);
			if (ret == 42)
				return (0);
			else if (ret)
				break ;
		}
		if (function(*cmds, env, fd))
			break ;
		reset_fds(fd);
		if (!((t_cmd *)(*cmds)->content)->nb)
			break ;
		*cmds = (*cmds)->next;
	}
	ft_wait(nb_wait);
	return (ret);
}
