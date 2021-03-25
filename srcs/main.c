/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:41:53 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/19 13:41:55 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd(char **cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
    {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
    else
    {
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			printf("Command not found\n");
			//perror("shell");
			return (-1);
		}
		//error(CMD_ERR);
	}
	return (0);
}

static void	get_path(char **cmd)
{
	char	*path;
	char	*bin;
	char	**path_split;
	int		i;

	path = ft_strdup(getenv("PATH"));
	if (!path)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2))
	{
		path_split = ft_split(path, ':');
		free(path);
		i = 0;
		while (path_split[i])
		{
			bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[i]) + ft_strlen(cmd[0]) + 2));
			if (!bin)
				break ;
			ft_strlcat(bin, path_split[i], ft_strlen(path_split[i]) + ft_strlen(bin) + 1);
			ft_strlcat(bin, "/",  + ft_strlen(bin) + 2);
			ft_strlcat(bin, cmd[0], ft_strlen(cmd[0]) + ft_strlen(bin) + 1);
			if (!access(bin, F_OK))
				break ;
			free(bin);
			i++;
		}
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
		free(path);
}

int			main(void)
{
    char	*line;
    t_cmds	cmds;
    char	**cmd;
	int		ret;

    write(1, "$> ", 3);
	ret = get_next_line(0, &line);
    while (ret > 0) 
    {
		ret = 0;
		parse_cmd(line, &cmds);
		while (cmds.cmds)
		{
			cmd = (char **)cmds.cmds->content;
			if (cmd[0])
			{
				get_path(cmd);
				if (!is_built_in(cmd[0]))
					ret = exec_cmd(cmd);
				else
					exec_built_in(cmd);
			}
			if (!ret)
				free_array(cmd);
			cmds.cmds = cmds.cmds->next;
		}
		free(line);
		write(1, "$> ", 3);
		ret = get_next_line(0, &line);
	}
	if (ret < 0)
		error(RD_ERR);
    free(line);
    return (0);
}
