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

static void		init_cmd(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->out_flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->nb = 0;
	cmd->background = 0;
}

static int		ft_free(int err, char *dup, char **pipes, t_cmd *cmd_general)
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

static void		ft_fillcmd(t_cmd *cmd, t_cmd *main, size_t j, size_t size)
{
	cmd->nb = size - j;
	if (cmd->in)
		free(cmd->in);
	if (cmd->out)
		free(cmd->out);
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->nb_pipes = size;
	if (cmd->nb == size - 1 && main->in)
		cmd->in = ft_strdup(main->in);
	if (!cmd->nb && main->out)
		cmd->out = ft_strdup(main->out);
}

static int		ft_fillstruct(char **lines, int i, t_cmd *main, t_list **cmds)
{
	char	*dup;
	size_t	size;
	size_t	j;
	t_cmd	*cmd;
	char	**pipes;

	dup = ft_strdup(lines[i]);
	if (!(main->cmd = tokenize(dup, " \t\n", main, 1)))
		return (-ft_free(1, dup, NULL, main));
	if (!(pipes = tokenize(lines[i++], "|", NULL, 0)))
		return (-ft_free(1, dup, NULL, main));
	j = 0;
	size = ft_arraysize(pipes);
	while (j < size)
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		init_cmd(cmd);
		if (!(cmd->cmd = tokenize(pipes[j++], " \t\n", cmd, 1)))
			return (-ft_free(1, dup, NULL, main));
		ft_fillcmd(cmd, main, j, size);
		ft_lstadd_back(cmds, ft_lstnew(cmd));
	}
	ft_free(0, dup, pipes, main);
	return (0);
}

int				parse_cmd(char *line, t_list **cmds)
{
	t_cmd	*cmd_general;
	char	**lines;
	size_t	i;

	i = 0;
	if (!line || check_line(line))
		return (print_error_str(NULL, msg_syn_err(check_line(line))) + 2);
	if (!(lines = tokenize(line, ";", NULL, 0)))
		return (ft_free(1, NULL, NULL, NULL));
	while (i < ft_arraysize(lines))
	{
		cmd_general = (t_cmd *)malloc(sizeof(t_cmd));
		init_cmd(cmd_general);
		if (ft_fillstruct(lines, i, cmd_general, cmds) < 0)
			return (1);
		i++;
	}
	free_array(lines);
	return (0);
}
