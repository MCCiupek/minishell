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

//static char	*fill_line(char *line, t_list *cmds, t_list *hist, t_list *env)
static char	*fill_line(char *line, t_list *hist, t_list *env)
{
	char	buf[6];
	int hist_pos;
	int r;
	int i;

	buf[0] = '\0';
	//if (!cmds)
	//	printf("blabala\n"); //à remove qd on se servira de cmds
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
		else if (!ft_strncmp(buf, CTRL_C, 1))
			return ("\n");
		else if (!ft_strncmp(buf, CTRL_D, 1))
		{
			if (!i)
				builtin_exit(NULL, env);
			continue ;
		}
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

//char		*read_line(t_list *env, t_list *cmds, t_list *hist)
char		*read_line(t_list *env, t_list *hist)
{
	char	*line;
	char	*tmp;

	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line)
		printf("ERROR\n"); //à modif
	line[0] = '\0';
	tmp = line;
	line = fill_line(line, hist, env);
	//line = fill_line(line, cmds, hist, env);
	write(STDOUT_FILENO, "\n", 1);
	if (!env)
		printf("fzjeo");
	return (line);
}

void		print_prompt(t_list *env)
{
	char 	*tmp[4];

	tmp[0] = ft_strdup("echo");
	tmp[1] = ft_strdup("-n");
	tmp[2] = ft_strdup("$LOGNAME");
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

t_list	*update_hist(char *line, t_list *hist)
{
	char *tmp;
	//t_list	*lst;
	
	if (ft_strncmp(line, "\n", ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		ft_lstadd_front(&hist, ft_lstnew(tmp));
	}
	/*lst = hist;
	printf("-----STATE OF HISTORY-----\n");
	while (lst)
	{
		printf("%s\n", lst->content);
		lst = lst->next;
	}
	printf("--------------------------\n");*/
	return (hist);
}

int			main(int argc, char **argv, char **envp)
{
    char	*line;
    t_list	*cmds;
	t_list	*env;
	t_list	*hist;
	int		ret;

	(void)argc;
	(void)argv;
    env = dup_env(envp);
	//cmds = (t_list *)malloc(sizeof(t_list));
	set_sig();
	hist = NULL;
	ret = 0;
	while (1)
	{
		cmds = NULL;
		line = NULL;
		print_prompt(env);
		term_on();
		//line = read_line(env, cmds, hist);
		line = read_line(env, hist);
		term_off();
		hist = update_hist(line, hist);
		parse_cmd(line, &cmds);
		ret = exec_cmds(cmds, env, ret);
		ft_lstclear(&cmds, free_t_cmd);
	}
    return (0);
}
