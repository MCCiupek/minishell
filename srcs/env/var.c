/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:24:19 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/12 14:24:24 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_quote(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	add_backslash(int i, char **cmd)
{
	char	*tmp;
	char	*old;

	tmp = ft_strdup(*cmd + i);
	(*cmd)[i] = '\\';
	(*cmd)[i + 1] = '\0';
	old = *cmd;
	*cmd = ft_strjoin(old, tmp);
	free(old);
	free(tmp);
}

char	*replace_env_var(char *cmd, char *quotes, int skip_quotes, int export)
{
	int		quote;
	t_infos	inf;

	inf.i = -1;
	inf.c = 0;
	quote = contains_quote(cmd);
	while (cmd && cmd[++(inf.i)])
	{
		skip_in_cmd(&cmd, &inf, skip_quotes, quotes);
		if (!cmd[inf.i])
			break ;
	}
	inf.i = -1;
	while (cmd && cmd[++(inf.i)])
	{
		if (cmd[inf.i] == '$' && inf.c != '\'' && cmd[inf.i + 1])
			determine_dollar_behavior(export, quote, &cmd, &inf);
		if (!cmd[inf.i])
			break ;
	}
	return (cmd);
}

int	replace_in_cmd(t_cmd *cmd, char *quotes)
{
	int	i;

	i = 0;
	cmd->cmd[0] = replace_env_var(cmd->cmd[0], quotes, 1, 0);
	while (cmd->cmd[++i])
	{
		if (ft_strncmp(cmd->cmd[0], "echo", 4) && \
			ft_strncmp(cmd->cmd[0], "export", 6))
			cmd->cmd[i] = replace_env_var(cmd->cmd[i], quotes, \
			ft_strncmp(cmd->cmd[0], "echo", 4), 0);
	}
	if (cmd->in)
		cmd->in = replace_env_var(cmd->in, quotes, 1, 0);
	if (cmd->out)
		cmd->out = replace_env_var(cmd->out, quotes, 1, 0);
	return (0);
}
