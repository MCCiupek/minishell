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

pid_t	pid;
t_list	*env;

static int	get_absolute_path(char **cmd)//, t_list *env)
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

static int	exec_cmd(t_list **cmds)//, t_list *env)
{
	int		tmp[2];
	int		fd[2];
	int		fdpipe[2];
	//pid_t	pid;
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
			exec_built_in(cmd->cmd, env);
		else
		{
			pid = fork();
			if (pid < 0)
				error(FRK_ERR);
			else if (!pid)
			{

					get_absolute_path(cmd->cmd);//, env);
					if (execve(cmd->cmd[0], cmd->cmd, NULL))
					{
						dup2(tmp[WRITE], WRITE);
						printf("%s : [%d] %s\n", cmd->cmd[0], errno, strerror(errno));
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
	return (0);
}

char	*history_up(int hist_pos, t_list *hist)
{
	t_list	*tmp;

	if (!hist)
		return (NULL);
	tmp = hist;
	while (hist_pos > 0 && tmp)
	{
		tmp = tmp->next;
		hist_pos--;
	}
	ft_putstr_fd(tmp->content, STDOUT_FILENO);
	return (tmp->content);
}

static char	*fill_line(char *line, t_cmds *cmds, t_list *hist)
{
	char	buf[6];
	int hist_pos;
	int r;
	int i;

	buf[0] = '\0';
	if (!cmds)
		printf("blabala\n"); //à remove qd on se servira de cmds
	i = 0;
	hist_pos = 0;
	while (buf[0] != '\n')
	{
		r = read(STDIN_FILENO, buf, 5);
		if (!r)
			return (NULL);
		if (!ft_strncmp(buf, UP, 4))
		{
			line = ft_strdup(history_up(hist_pos, hist));
			hist_pos++;
		}
		else if (!ft_strncmp(buf, DOWN, 4))
			ft_putstr_fd("history down!!\n", STDOUT_FILENO);
		else if (!ft_strncmp(buf, RIGHT, 4))
			printf("cursor position!!\n");
		else if (!ft_strncmp(buf, LEFT, 4))
			printf("cursor position!!\n");
		else if (!ft_strncmp(buf, CTRL_D, 2))
			builtin_exit(NULL, env);
		else if (r > 0)
		{
			if (r == 1 && buf[0] != '\n' && buf[0] != '\034')
			{
				ft_putchar_fd(buf[0], STDOUT_FILENO);
				line[i] = buf[0];
				i++;
				line[i] = '\0';
			}
		}
	}
	return (line);
}

//char		*read_line(t_list *env, t_cmds *cmds, t_list *hist)
char		*read_line(t_cmds *cmds, t_list *hist)
{
	char	*line;
	char	*tmp;

	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line)
		printf("ERROR\n"); //à modif
	line[0] = '\0';
	tmp = line;
	line = fill_line(line, cmds, hist);
	write(STDOUT_FILENO, "\n", 1);
	if (!env)
		printf("fzjeo");
	return (line);
}

void		print_prompt()//t_list *env)
{
	char 	*tmp[4];

	tmp[0] = ft_strdup("echo");
	tmp[1] = ft_strdup("-n");
	tmp[2] = ft_strdup("$USER");
	tmp[2] = replace_env_var(tmp[2], "\'\"", env, 0);
	tmp[3] = NULL;
	ft_putstr_fd("\033[0;33m", STDOUT_FILENO);
	built_in_echo(tmp, env);
    write(STDOUT_FILENO, "@minishell", 12);
   	write(STDOUT_FILENO, "\033[0m", 4);
	ft_putchar_fd(':', STDOUT_FILENO);
	free(tmp[2]);
	tmp[2] = ft_strdup("$PWD");
	tmp[2] = replace_env_var(tmp[2], "\'\"", env, 0);
	ft_putstr_fd("\e[1;34m", STDOUT_FILENO);
	built_in_echo(tmp, env);
	write(STDOUT_FILENO, "\033[0m", 4);
	ft_putstr_fd("$\e[0m ", STDOUT_FILENO);
}

void  ctrl_c_handler(int sig)
{
	(void)sig;
	signal(SIGINT, ctrl_c_handler);
	ft_putchar_fd('\n', STDOUT_FILENO);
	print_prompt();
}

void  ctrl_bs_handler(int sig)
{
	signal(SIGQUIT, ctrl_bs_handler);
	if (!kill(pid, sig))
		write(1, "^\\Quit: 3\n", 10);
}

void		exec_cmds(t_cmds *cmds)//, t_list *env)
{
	int		ret;
	t_cmd	*cmd;

	ret = 1;
	while (cmds->cmds)
	{
		if (cmd)
			ret = cmd->err;
		else
			ret = 0;
		cmd = (t_cmd *)cmds->cmds->content;
		cmd->err = ret;
		replace_in_cmd(cmd, "\'\"", env);
		if (cmd->cmd[0])
			exec_cmd(&cmds->cmds);//, env);
		cmds->cmds = cmds->cmds->next;
	}
}

t_list	*update_hist(char *line, t_list *hist)
{
	char *tmp;
	t_list	*lst;
	
	if (ft_strncmp(line, "\n", ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		ft_lstadd_front(&hist, ft_lstnew(tmp));
	}
	lst = hist;
	printf("-----STATE OF HISTORY-----\n");
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	printf("--------------------------\n");
	return (hist);
}

int			main(int argc, char **argv, char **envp)
{
    char	*line;
    t_cmds	*cmds;
  //  t_cmd	*cmd;
	//int		ret;
	//t_list	*env;
	t_list	*hist;
	struct termios term;

	(void)argc;
	(void)argv;
    env = dup_env(envp);
	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	cmds->cmds = NULL;
	tcgetattr(fileno(stdin), &term);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_bs_handler);
	term.c_lflag &= ~(ICANON | ECHO);// | ISIG); // | ECHOCTL);
    tcsetattr(fileno(stdin), TCSANOW, &term);
	line = NULL;
	hist = NULL;
	while (1)
	{
		print_prompt();//env);
		//line = read_line(env, cmds, hist);
		line = read_line(cmds, hist);
		hist = update_hist(line, hist);
		parse_cmd(line, cmds);
		exec_cmds(cmds);//, env);
	}
    free(line);
	builtin_exit(NULL, env);
	term.c_lflag |= ICANON | ECHO;// | ISIG; //ECHOCTL;
	tcsetattr(fileno(stdin), 0, &term);
    return (0);
}
