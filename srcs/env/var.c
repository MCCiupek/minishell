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

static char	*ft_skipchar(char *s, int i)
{
	char	*copy;
	char	*tmp;

	if (s)
	{
		if (i >= ft_strlen(s))
			return (s);
		if (!(tmp = (char *)malloc(sizeof(s) * (i + 1))))
			return (NULL);
		ft_strlcpy(tmp, s, i + 1);
		if (i < ft_strlen(s) - 1)
			copy = ft_strjoin(tmp, &s[i + 1]);
		else
			copy = ft_strdup(tmp);
		free(s);
		free(tmp);
		return (copy);
	}
	return (NULL);
}

static char	*ft_strnchr(char *s, char *chars)
{
	int	i;

	i = 0;
	while (!ft_strchr(chars, s[i]))
		i++;
	return (&s[i]);
}

static int	ft_locnchr(char *s, char *chars)
{
	int	i;

	i = 0;
	while (!ft_strchr(chars, s[i]))
		i++;
	return (i);
}

static char	*jf(char *s, char *replacement, char *copy, int i)
{
	char	*copy_tmp;

	copy_tmp = ft_strjoin(copy, replacement);
	free(copy);
	copy = ft_strjoin(copy_tmp, ft_strnchr(&s[i], " \\"));
	free(copy_tmp);
	free(s);
	return (copy);
}

static char	*get_num(int n, char *s, char *copy, int i)
{
	char	*res;
	char	*num;

	num = ft_itoa(n);
	res = jf(s, num, copy, i);
	free(num);
	return (res);
}

static char	*final_join(char *copy, char *s, int i)
{
	char	*copy_tmp;

	copy_tmp = ft_strjoin(copy, ft_strnchr(&s[i], " \\"));
	free(copy);
	free(s);
	return (copy_tmp);
}

static char	*replace(char *s, int i, t_list *env, int err)
{
	t_list	*tmp;
	char	*cp;

	tmp = env;
	if (s)
	{
		if (!(cp = (char *)malloc(sizeof(s) * (i + 1))))
			return (NULL);
		ft_strlcpy(cp, s, i + 1);
		if (!ft_strncmp("?", &s[i] + 1, ft_locnchr(&s[i], " \\") - 1))
			return (get_num(err, s, cp, i));
		if (!ft_strncmp("$", &s[i] + 1, ft_locnchr(&s[i], " \\") - 1))
			return (get_num(g_pid, s, cp, i));
		while (tmp)
		{
			if (!ft_strncmp((char *)tmp->content, &s[i] + 1,
				ft_locnchr(&s[i], " \\") - 1))
				return (jf(s, ft_strchr((char *)tmp->content, '=') + 1, cp, i));
			tmp = tmp->next;
		}
		return (final_join(cp, s, i));
	}
	return (s);
}

char		*replace_env_var(char *cmd, char *quotes, t_list *env, int err)
{
	int		i;
	char	c;
	char	*tmp;

	i = -1;
	c = 0;
	if (!cmd)
		return (NULL);
	while (cmd && cmd[++i])
	{
		if (cmd[i] && !c && ft_strchr(quotes, cmd[i]))
		{
			c = cmd[i];
			cmd = ft_skipchar(cmd, i);
		}
		if (c && cmd[i] == c)
		{
			c = 0;
			cmd = ft_skipchar(cmd, i);
		}
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
