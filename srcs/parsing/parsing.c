/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_free(int err, char *dup, char **pipes, t_cmd *cmd_general)
{
	if (err)
		perror("tokenize");
	if (dup)
		free(dup);
	if (pipes)
		free_array(pipes);
	if (cmd_general)
		free_t_cmd(cmd_general);
	return (1);
}

static void	ft_fill_cmd(t_cmd *cmd, t_cmd *main, size_t j, size_t size)
{
	(void)main;
	cmd->nb = size - j;
	/*if (cmd->in)
		free(cmd->in);
	if (cmd->out)
		free(cmd->out);
	cmd->in = NULL;
	cmd->out = NULL;*/
	cmd->nb_pipes = size;
	/*if (cmd->nb == size - 1 && main->in)
		cmd->in = ft_strdup(main->in);
	if (!cmd->nb && main->out)
		cmd->out = ft_strdup(main->out);*/
}

static int	ft_fill_lst(char **pipes, t_cmd *main, t_list **cmds)
{
	t_cmd	*cmd;
	size_t	size;
	size_t	j;

	j = 0;
	size = ft_arraysize(pipes);
	while (j < size)
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		ft_init_cmd(cmd);
		cmd->cmd = tokenize(pipes[j++], " \t\n", cmd, 1);
		if (!cmd->cmd)
			return (0);
		ft_fill_cmd(cmd, main, j, size);
		ft_lstadd_back(cmds, ft_lstnew(cmd));
	}
	return (1);
}

static int	ft_fill_struct(char **lines, int i, t_cmd *main, t_list **cmds)
{
	char	*dup;
	char	**pipes;

	dup = ft_strdup(lines[i]);
	main->cmd = tokenize(dup, " \t\n", main, 1);
	if (!main->cmd)
		return (-ft_free(0, dup, NULL, NULL));
	pipes = tokenize(lines[i++], "|", NULL, 0);
	if (!pipes)
		return (-ft_free(1, dup, NULL, main));
	if (!ft_fill_lst(pipes, main, cmds))
		return (-ft_free(1, dup, NULL, main));
	ft_free(0, dup, pipes, main);
	return (0);
}

int	parse_cmd(char *line, t_list **cmds)
{
	t_cmd	*cmd_general;
	char	**lines;
	size_t	i;

	i = 0;
	cmd_general = NULL;
	if (!line || check_line(line))
		return (g_gbl.exit = print_error_str(NULL, msg_syn_err(check_line(line))) + 2);
	lines = tokenize(line, ";", NULL, 0);
	if (!ft_strncmp(lines[0], "\"\"", 2) || !ft_strncmp(lines[0], "\'\'", 2))
	{
		free_array(lines);
		return (g_gbl.exit = print_error("", CMD_ERR) + 127);
	}
	if (!lines)
		return (g_gbl.exit = print_error(NULL, CMD_ERR) + 1);
	while (i < ft_arraysize(lines))
	{
		cmd_general = (t_cmd *)malloc(sizeof(t_cmd));
		ft_init_cmd(cmd_general);
		if (ft_fill_struct(lines, i, cmd_general, cmds) < 0)
		{
			free_t_cmd(cmd_general);
			free_array(lines);
			return (g_gbl.exit = 1);
		}
		i++;
	}
	free_array(lines);
	return (0);
}
