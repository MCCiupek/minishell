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

static void	print_prompt(t_list *env)
{
	char	*tmp[4];

	tmp[0] = ft_strdup("echo");
	tmp[1] = ft_strdup("-n");
	tmp[2] = ft_strdup("$LOGNAME");
	tmp[2] = replace_env_var(tmp[2], "\'\"", env, 0);
	tmp[3] = NULL;
	ft_putstr_fd("\033[0;33m", STDERROR);
	write(STDERROR, tmp[2], ft_strlen(tmp[2]));
	write(STDERROR, "@minishell", 10);
	write(STDERROR, "\033[0m", 4);
	ft_putchar_fd(':', STDERROR);
	free(tmp[2]);
	tmp[2] = ft_strdup("$PWD");
	tmp[2] = replace_env_var(tmp[2], "\'\"", env, 0);
	ft_putstr_fd("\e[1;34m", STDERROR);
	write(STDERROR, tmp[2], ft_strlen(tmp[2]));
	write(STDERROR, "\033[0m", 4);
	ft_putstr_fd("$\e[0m ", STDERROR);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
}

static void	handle_line(char *line, t_list *cmds, t_list *hist, t_list *env)
{
	int ret;
	int err;

	ret = 0;
	hist = update_hist(line, hist);
	if ((err = parse_cmd(line, &cmds)))
		ret = err;
	else if (!(((t_cmd *)cmds->content)->cmd[0]))
		ret = 0;
	else if (ft_strncmp(((t_cmd *)cmds->content)->cmd[0], "exit", 4))
		ret = exec_cmds(cmds, env, ret, hist);
	else
	{
		free(line);
		builtin_exit(cmds, env, hist, 0, 0);
	}
}

static char	*get_line(int argc, char **argv, t_list *env, t_list *hist)
{
	char	*line;

	line = NULL;
	term_on();
	if (argc > 2 && !ft_strncmp(argv[1], "-c", 2))
		line = argv[2];
	else
		line = read_line(hist, env);
	term_off();
	return (line);
}

int			main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*cmds;
	t_list	*env;
	t_list	*hist;

	env = dup_env(envp);
	set_sig();
	hist = NULL;
	while (1)
	{
		cmds = NULL;
		if (argc == 1)
			print_prompt(env);
		line = get_line(argc, argv, env, hist);
		if (line)
		{
			handle_line(line, cmds, hist, env);
			if (argc < 2)
				free(line);
			ft_lstclear(&cmds, free_t_cmd);
		}
		if (argc > 2)
			break ;
	}
	return (0);
}
