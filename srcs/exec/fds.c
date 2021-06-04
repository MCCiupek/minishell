/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:27:57 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:27:59 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(t_cmd *cmd, int mode, int tmp, int fd)
{
	int		fd_ret;
	char	*path;
	int		flags;

	path = cmd->out;
	flags = cmd->out_flags;
	if (fd == READ)
	{
		path = cmd->in;
		flags = O_RDONLY;
	}
	if (path)
	{
		fd_ret = open(path, flags, mode);
		if (fd_ret < 0)
		{
			perror("Couldn't open file");
			return (-1);
		}
	}
	else
		fd_ret = dup(tmp);
	return (fd_ret);
}

int	open_close_fds(t_cmd *cmd, int fd[2], int tmp[2], int fdpipe[2])
{
	dup2(fd[READ], READ);
	close(fd[READ]);
	if (!cmd->nb)
	{
		fd[WRITE] = get_fd(cmd, 0644, tmp[WRITE], WRITE);
		if (fd[WRITE] == -1)
			return (-1);
	}
	else
	{
		pipe(fdpipe);
		fd[WRITE] = fdpipe[WRITE];
		fd[READ] = fdpipe[READ];
	}
	dup2(fd[WRITE], WRITE);
	close(fd[WRITE]);
	return (0);
}
