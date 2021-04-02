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

static int	exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		old_pfd[2];
	int		new_pfd[2];

	status = 0;
	if (cmd->nb)
	{
		if (pipe(new_pfd) < 0)
		{
			printf("pipe failed\n");
			return (-1);
		}
	}
	pid = fork();
	if (pid < 0)
		error(FRK_ERR);
	else if (pid > 0)
    {
		//printf("[parent] nb cmds = %zu\n", cmd->nb_pipes);
		if (cmd->nb_pipes > 1 && cmd->nb < cmd->nb_pipes - 1)			// if there is a previous cmd
		{
			close(old_pfd[0]);
			close(old_pfd[1]);
		}
		if (cmd->nb_pipes > 1 && cmd->nb)							// if there is a next cmd
		{
			old_pfd[0] = new_pfd[0];
			old_pfd[1] = new_pfd[1];
		}
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else 
	{
		//printf("[child] nb cmds = %zu\n", cmd->nb_pipes);
		if (cmd->nb == cmd->nb_pipes - 1 && cmd->in)
    	{
        	if ((old_pfd[0] = open(cmd->in, O_RDONLY)) < 0)
			{
				perror("Couldn't open input file");
            	return (-1);
			}
			dup2(old_pfd[0], STDIN_FILENO);
        	close(old_pfd[0]);
    	}
		if (!cmd->nb && cmd->out)
    	{
			if ((old_pfd[1] = open(cmd->out, cmd->out_flags, 0644)) < 0)
			{
				perror("Couldn't open output file");
            	return (-1);
			}
			dup2(old_pfd[1], STDOUT_FILENO);
			close(old_pfd[1]);
    	}
		if (cmd->nb_pipes > 1 && cmd->nb < cmd->nb_pipes - 1)			// if there is a previous cmd
		{
			dup2(old_pfd[0], STDIN_FILENO);
			close(old_pfd[0]);
			close(old_pfd[1]);
		}
		if (cmd->nb_pipes > 1 && cmd->nb)							// if there is a next cmd
		{
			close(new_pfd[0]);
            dup2(new_pfd[1], STDOUT_FILENO);
            close(new_pfd[1]);
		}
		if (execve(cmd->cmd[0], cmd->cmd, NULL) < 0)
		{
            printf("Command not found\n");
            return (-1);
        }
	}
	if (cmd->nb_pipes > 1)
	{
		close(old_pfd[0]);
		close(old_pfd[1]);
	}
	return (0);
}
/*
static int	exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		pfd[2];

	status = 0;
	pid = fork();
	if (pid == -1)
		error(FRK_ERR);
	else if (pid > 0)
    {
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
    else
    {
		if (cmd->in)
    	{
        	if ((pfd[0] = open(cmd->in, O_RDONLY)) < 0)
			{
				perror("Couldn't open input file");
            	return (-1);
			}
        	dup2(pfd[0], STDIN_FILENO);
        	close(pfd[0]);
    	}
		if (cmd->out)
    	{
			if ((pfd[1] = open(cmd->out, cmd->out_flags, 0644)) < 0)
			{
				perror("Couldn't open output file");
            	return (-1);
			}
			dup2(pfd[1], STDOUT_FILENO);
			close(pfd[1]);
    	}
		//printf("%zu\n", ft_arraysize(cmd->cmd));
		if (execve(cmd->cmd[0], cmd->cmd, NULL) < 0)
		{
			printf("Command not found\n");
			//perror("shell");
			return (-1);
		}
		//error(CMD_ERR);
	}
	return (0);
}
*/
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
			//printf("%s\n", (char *)tmp->content);
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

int			main(int argc, char **argv, char **envp)
{
    char	*line;
    t_cmds	*cmds;
    t_cmd	*cmd;
	int		ret;
	t_list	*env;

	(void)argc;
	(void)argv;
    env = dup_env(envp);
    write(1, "$> ", 3);
	ret = get_next_line(0, &line);
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmds = NULL;
    while (ret > 0)
    {
		ret = 0;
		parse_cmd(line, cmds);
		while (cmds->cmds)
		{
			cmd = (t_cmd *)cmds->cmds->content;
			//printf("cmd : %s %s\n", cmd->cmd[0], cmd->cmd[1]);
			//printf("in : %s\n", cmd->in);
			//printf("out : %s\n", cmd->out);
			if (cmd->cmd[0])
			{
				if (!is_built_in(cmd->cmd[0]))
				{
					get_absolute_path(cmd->cmd, env);
					ret = exec_cmd(cmd);
				}
				else
					exec_built_in(cmd->cmd, env);
			}
			if (!ret)
				free_array(cmd->cmd);
			cmds->cmds = cmds->cmds->next;
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
