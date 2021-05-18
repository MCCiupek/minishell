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

static char	*ft_skip(char *cmd, int i, int open, char *c)
{
	*c = 0;
	if (open)
		*c = cmd[i];
	return (ft_skipchar(cmd, i));
}

char		*replace_env_var(char *cmd, char *quotes, t_list *env, int err)
{
	int		i;
	char	c;
	char	*tmp;

	i = -1;
	c = 0;
	while (cmd && cmd[++i])
	{
		if (cmd[i] && !c && ft_strchr(quotes, cmd[i]))
			cmd = ft_skip(cmd, i, 1, &c);
		if (c && cmd[i] == c)
			cmd = ft_skip(cmd, i, 0, &c);
		if (cmd[i] == '$' && c != '\'' && cmd[i + 1])
		{
			tmp = ft_strdup(cmd);
			free(cmd);
			cmd = replace(ft_strtrim(tmp, &c), i, env, err);
			free(tmp);
		}
		if (!cmd[i])
			break ;
	}
	return (cmd);
}

int			replace_in_cmd(t_cmd *cmd, char *quotes, t_list *env)
{
	int i;

	i = -1;
	while (cmd->cmd[++i])
		cmd->cmd[i] = replace_env_var(cmd->cmd[i], quotes, env, cmd->err);
	if (cmd->in)
		cmd->in = replace_env_var(cmd->in, quotes, env, cmd->err);
	if (cmd->out)
		cmd->out = replace_env_var(cmd->out, quotes, env, cmd->err);
	return (0);
}
