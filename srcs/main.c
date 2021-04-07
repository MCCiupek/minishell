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

# define READ 0
# define WRITE 1

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

static int	exec_cmd(t_list **cmds, t_list *env)
{
	int		tmp[2];
	int		fd[2];
	int		fdpipe[2];
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	cmd = (t_cmd *)(*cmds)->content;
	get_absolute_path(cmd->cmd, env);
	tmp[READ] = dup(READ);
	tmp[WRITE] = dup(WRITE);
	status = 0;
	if (cmd->in)
	{
		if ((fd[READ] = open(cmd->in, O_RDONLY)) < 0)
		{
			perror("Couldn't open input file");
           	return (-1);
		}
	}
	else
		fd[READ] = dup(tmp[READ]);
	while (1)
	{
		dup2(fd[READ], READ);
		close(fd[READ]);
		if (!cmd->nb)
		{
			if (cmd->out)
			{
				if ((fd[WRITE] = open(cmd->out, cmd->out_flags, 0644)) < 0)
				{
					perror("Couldn't open output file");
					return (-1);
				}
			}
			else
				fd[WRITE] = dup(tmp[WRITE]);
		}
		else
		{
			pipe(fdpipe);
			fd[WRITE] = fdpipe[WRITE];
			fd[READ] = fdpipe[READ];
		}
		dup2(fd[WRITE], WRITE);
		close(fd[WRITE]);
		pid = fork();
		if (pid < 0)
			error(FRK_ERR);
		else if (pid > 0)
		{
			//if (cmd->nb)
			//	cmd = (t_cmd *)cmds->next->content;
		}
		else if (!pid)
		{
			if (execve(cmd->cmd[0], cmd->cmd, NULL))
			{
				dup2(tmp[WRITE], WRITE);
				printf("%s : [%d] %s\n", cmd->cmd[0], errno, strerror(errno));
				return (-1);
			}
		}
		if (!cmd->nb)
			break ;
		cmd = (t_cmd *)(*cmds)->next->content;
	}
	dup2(tmp[READ], READ);
	dup2(tmp[WRITE], WRITE);
	close(tmp[READ]);
	close(tmp[WRITE]);
	if (!cmd->background)
		waitpid(pid, &status, 0);
	free_array(cmd->cmd);
	return (0);
}
/*
static int	exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		stdoutfd;
	int		old_pfd[2];
	int		new_pfd[2];

	status = 0;
	if (cmd->in) // cmd->nb == cmd->nb_pipes - 1 && 
    {
		//close(old_pfd[1]);
       	if ((old_pfd[0] = open(cmd->in, O_RDONLY)) < 0)
		{
			perror("Couldn't open input file");
           	return (-1);
		}
		//printf("dup old 0 et close old 0\n");
		//dup2(old_pfd[0], STDIN_FILENO);
       	//close(old_pfd[0]);
		//close(old_pfd[1]);
    }
	if (cmd->out) // !cmd->nb && 
    {
		//close(old_pfd[0]);
		if ((old_pfd[1] = open(cmd->out, cmd->out_flags, 0644)) < 0)
		{
			perror("Couldn't open output file");
           	return (-1);
		}
		//printf("dup old 1 et close old 1 (fd = %d)\n", old_pfd[1]);
		//dup2(old_pfd[1], STDOUT_FILENO);
		//close(old_pfd[1]);
		//close(old_pfd[0]);
    }
	while (1)
	{
		if (cmd->nb)
		{
			printf("je pipe\n");
			if (pipe(new_pfd) < 0)
			{
				printf("pipe failed\n");
				return (-1);
			}
		}
		pid = fork();
		//printf("je fork\n");
		if (pid < 0)
			error(FRK_ERR);
		else if (pid > 0)			// PARENT
		{
			//printf("[parent] nb cmds = %zu\n", cmd->nb_pipes);
			if (cmd->nb < cmd->nb_pipes - 1)			// if there is a previous cmd
			{
				printf("[parent] close old 0 et 1\n");
				close(old_pfd[0]);
				close(old_pfd[1]);
			}
			if (cmd->nb)							// if there is a next cmd
			{
				printf("[parent] old = new\n");
				old_pfd[0] = new_pfd[0];
				old_pfd[1] = new_pfd[1];
			}
			//wait(&status);
			waitpid(pid, &status, 0);
			break ;
		}
		else 
		{
			stdoutfd = dup(STDOUT_FILENO);
			if (cmd->nb_pipes > 1 && cmd->nb < cmd->nb_pipes - 1)			// if there is a previous cmd
			{
				printf("[child] dup old 0, close old 0 et close old 1\n");
				dup2(old_pfd[0], STDIN_FILENO);
				close(old_pfd[0]);
				close(old_pfd[1]);
			}
			if (cmd->nb_pipes > 1 && cmd->nb)							// if there is a next cmd
			{
				printf("[child] close new 0, dup new 1 et close new 1\n");
				close(new_pfd[0]);
				dup2(new_pfd[1], STDOUT_FILENO);
				close(new_pfd[1]);
			}
			if (cmd->in)
			{
				printf("[child] dup old 0 et close old 0\n");
				dup2(old_pfd[0], STDIN_FILENO);
				close(old_pfd[0]);
			}
			if (cmd->out)
			{
				printf("[child] dup old 1 et close old 1\n");
				dup2(old_pfd[1], STDOUT_FILENO);
				close(old_pfd[1]);
			}
			//int i = 0;
			//while (cmd->cmd[i])
			//	printf("[CHILD] cmd : <%s>\n", cmd->cmd[i++]);
			if (execve(cmd->cmd[0], cmd->cmd, NULL))
			{
				dup2(stdoutfd, STDOUT_FILENO);
				printf("%d : %s\n", errno, strerror(errno));
				//printf("Command not found\n");
				return (-1);
			}
			kill(pid, SIGTERM);
		}
	}
	if (cmd->nb_pipes > 1)
	{
		printf("close old 0 et 1\n");
		close(old_pfd[0]);
		close(old_pfd[1]);
	}
	return (0);
}

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
			/*printf("in : %s\n", cmd->in);
			printf("out : %s\n", cmd->out);
			printf("n_pipes : %zu/%zu\n", cmd->nb, cmd->nb_pipes);*/
			if (cmd->cmd[0])
			{
				if (!is_built_in(cmd->cmd[0]))
					ret = exec_cmd(&cmds->cmds, env);
				else
					exec_built_in(cmd->cmd, env);
			}
			//if (!ret)
			//	free_array(cmd->cmd);
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
