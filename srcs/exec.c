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

static int	get_absolute_path(char **cmd, t_list *env)
{
	char	*path;
	char	*bin;
	char	**path_split;
	t_list	*tmp;
	int		i;

	path = NULL;
	bin = NULL;
	path_split = NULL;
	tmp = env;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		while (tmp)
		{
			if (!strncmp((char *)tmp->content, "PATH=", 5))
			{
				path = ft_strdup(&((char *)tmp->content)[5]);
				break;
			}
			tmp = tmp->next;
		}
		if (path == NULL)
			error(PATH_ERR);
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		i = 0;
		while (path_split[i])
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + ft_strlen(cmd[0]) + 2));
			if (!bin)
				break ;
			ft_strcat(bin, path_split[i]);
			ft_strcat(bin, "/");
			ft_strcat(bin, cmd[0]);
			if (!access(bin, F_OK))
				break ;
			free(bin);
			bin = NULL;
			i++;
		}
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
	return( bin == NULL ? 0 : 1);
}

static int	get_fd(t_cmd *cmd, int mode, int tmp, int fd)
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
		if ((fd_ret = open(path, flags, mode)) < 0)
		{
			perror("Couldn't open file");
           	return (-1);
		}
	}
	else
		fd_ret = dup(tmp);
	return (fd_ret);
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
		if (is_built_in(cmd->cmd[0]))
			exec_built_in(cmd->cmd, env, hist);
		else
		{
			pid = fork();
			if (pid < 0)
				error(FRK_ERR);
			else if (!pid)
			{

					get_absolute_path(cmd->cmd, env);
					if (execve(cmd->cmd[0], cmd->cmd, NULL))
					{
						dup2(tmp[WRITE], WRITE);
						perror("Command not find");
						*cmds = (*cmds)->next;
						return (-1);
					}
			}
		}
		if (!cmd->nb)
			break ;
		*cmds = (*cmds)->next;
	}
	dup2(tmp[READ], READ);
	dup2(tmp[WRITE], WRITE);
	close(tmp[READ]);
	close(tmp[WRITE]);
	if (!cmd->background)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
        cmd->err = WEXITSTATUS(status);
	return (cmd->err);
}

int		exec_cmds(t_list *cmds, t_list *env, int ret, t_list *hist)
{
	t_cmd	*cmd;

    cmd = NULL;
	while (cmds)
	{
		if (cmd && cmd->err)
			ret = cmd->err;
		cmd = (t_cmd *)cmds->content;
		cmd->err = ret;
		replace_in_cmd(cmd, "\'\"", env);
		if (cmd->cmd[0])
			ret = exec_cmd(&cmds, env, hist);
		cmds = cmds->next;
	}
    return (ret);
}