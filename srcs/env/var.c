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
	if (!open)
		*c = 0;
	if (open == 1)
		*c = cmd[i];
	return (ft_skipchar(cmd, i));
}

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

char	*replace_env_var(char *cmd, char *quotes, t_list *env, int skip_quotes, int export)
{
	int		i;
	int		len;
	char	c;
	char	*tmp;

	i = -1;
	c = 0;
	len = 0;
	int quote = 0;
	quote = contains_quote(cmd);
//	printf("cmd=%s with nbq=%i\n", cmd, quote);
	while (cmd && cmd[++i])
	{
		if (skip_quotes && cmd[i] && !c && ft_strchr(quotes, cmd[i]))
			cmd = ft_skip(cmd, i, 1, &c);
		if (skip_quotes && (c == '\"' || !c) && cmd[i] == '\\' && !ft_isalnum(cmd[i + 1]))
			cmd = ft_skip(cmd, i++, -1, &c);
		if (skip_quotes && c && cmd[i] == c)
			cmd = ft_skip(cmd, i, 0, &c);
	/*	if (cmd[i] == '$' && c != '\'' && cmd[i + 1])
		{
			len = 0;
			tmp = ft_strdup(cmd);
			free(cmd);
			cmd = replace(ft_strtrim(tmp, &c), i, env, &len);
			printf("cmd=%s\n", cmd);
			if (!is_in_env(tmp, env, i) && i > 0)
				i--;
		//	if (len > 0)
		//		i += len - 1;
			free(tmp);
		}*/
		if (!cmd[i])
			break ;
	}
	i = -1;
	while (cmd && cmd[++i])
	{
		if (cmd[i] == '$' && c != '\'' && cmd[i + 1])
		{
			if (export == 0 || (export == 1 && quote == 0))
			{
				len = 0;
				tmp = ft_strdup(cmd);
				free(cmd);
				cmd = replace(ft_strtrim(tmp, &c), i, env, &len);
				if (!is_in_env(tmp, env, i) && i > 0)
					i--;
			//	if (len > 0)
			//		i += len - 1;
				free(tmp);
			}
			else
			{
				tmp = ft_strdup(cmd + i);
				cmd[i] = '\\';
				cmd[i + 1] = '\0';
				char *old;
				old = cmd;
				cmd = ft_strjoin(old, tmp);
				free(old);
				free(tmp);
				i++;
			}
		}
		if (!cmd[i])
			break ;
	}
	return (cmd);
}

int	replace_in_cmd(t_cmd *cmd, char *quotes, t_list *env)
{
	int	i;

	i = 0;
	cmd->cmd[0] = replace_env_var(cmd->cmd[0], quotes, env, 1, 0);
	while (cmd->cmd[++i])
	{
		if (ft_strncmp(cmd->cmd[0], "echo", 4) && ft_strncmp(cmd->cmd[0], "export", 6))
			cmd->cmd[i] = replace_env_var(cmd->cmd[i], quotes, env, ft_strncmp(cmd->cmd[0], "echo", 4), 0);
	}
	if (cmd->in)
		cmd->in = replace_env_var(cmd->in, quotes, env, 1, 0);
	if (cmd->out)
		cmd->out = replace_env_var(cmd->out, quotes, env, 1, 0);
	return (0);
}
