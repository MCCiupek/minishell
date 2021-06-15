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

static void	free_tmp(char *tmp1, char *tmp2, char *tmp3)
{
	if (tmp1)
		free(tmp1);
	if (tmp2)
		free(tmp2);
	if (tmp3)
		free(tmp3);
}

static void	print_prompt(t_list *env)
{
	char	*tmp[4];

	tmp[0] = ft_strdup("echo");
	tmp[1] = ft_strdup("-n");
	tmp[2] = ft_strdup("$LOGNAME");
	tmp[2] = replace_env_var(tmp[2], "\'\"", env, 0);
	tmp[3] = NULL;
	ft_putstr_fd("\033[0;33m", STDERROR);
	if (ft_strlen(tmp[2]) == 0)
		tmp[2] = ft_strdup("user42");
	write(STDERROR, tmp[2], ft_strlen(tmp[2]));
	write(STDERROR, "@minishell", 10);
	write(STDERROR, "\033[0m", 4);
	ft_putchar_fd(':', STDERROR);
	free(tmp[2]);
	tmp[2] = ft_strdup("$PWD");
	tmp[2] = replace_env_var(tmp[2], "\'\"", env, 0);
	tmp[2] = check_prompt_pwd(tmp[2]);
	ft_putstr_fd("\e[1;34m", STDERROR);
	write(STDERROR, tmp[2], ft_strlen(tmp[2]));
	write(STDERROR, "\033[0m", 4);
	ft_putstr_fd("$\e[0m ", STDERROR);
	free_tmp(tmp[0], tmp[1], tmp[2]);
}

static int	handle_line(char *line, t_params *params, int ret)
{
	int	err;

	params->hist = update_hist(line, params->hist);
	err = parse_cmd(line, &params->cmds);
	if (err)
		ret = err;
	else if (!(((t_cmd *)params->cmds->content)->cmd[0]))
		ret = 0;
	else if (ft_strncmp(((t_cmd *)params->cmds->content)->cmd[0], "exit", 4))
		ret = exec_cmds(params, ret);
	else
	{
		free(line);
		builtin_exit(params->cmds, params->env, params->hist, 0);
	}
	return (ret);
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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_params	params;
	int			ret;

	params.env = dup_env(envp);
	set_sig();
	params.hist = NULL;
	ret = 0;
	while (1)
	{
		params.cmds = NULL;
		if (argc == 1)
			print_prompt(params.env);
		line = get_line(argc, argv, params.env, params.hist);
		if (line)
		{
			ret = handle_line(line, &params, ret);
			if (ret != 1 && argc < 2)
				free(line);
			ft_lstclear(&params.cmds, free_t_cmd);
		}
		if (argc > 2)
			break ;
	}
	exit(EXIT_SUCCESS);
}
