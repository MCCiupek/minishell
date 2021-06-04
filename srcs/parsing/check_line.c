/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	ft_skipspaces(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(" \t", s[i]))
			return (s[i]);
		i++;
	}
	return (0);
}

static int	ft_isempty(char *c, char *next, char s, char *sep)
{
	int		empty;

	*c = 0;
	*next = 0;
	if (!ft_strchr(sep, s) && !ft_strchr(" \t", s))
		empty = 0;
	if (ft_strchr(sep, s))
		empty = 1;
	return (empty);
}

static char	ft_isrep(char *str, char *sep)
{
	int		i;
	int		empty;
	char	c;
	char	next;

	i = -1;
	empty = 1;
	while (++i < ft_strlen(str) - 1)
	{
		empty = ft_isempty(&c, &next, str[i], sep);
		if (ft_strchr(sep, str[i]) || ft_strchr(" \t", str[i]))
			c = str[i];
		if (c)
		{
			if (c == '>' && str[i + 1] && str[i + 1] == c)
				continue ;
			next = ft_skipspaces(&str[i + 1]);
			if ((!next || ft_strchr(sep, next)) && ft_strchr(" \t", c) && empty)
				return (next);
			if ((!next || ft_strchr(sep, next)) && ft_strchr(sep, c))
				return (str[i]);
		}
	}
	return (0);
}

char	*msg_syn_err(char token)
{
	char	*tokstr;
	char	*msg;

	if (token == '\n')
		tokstr = ft_strdup("`newline'");
	else
	{
		tokstr = (char *)malloc(sizeof(char) * 4);
		tokstr[0] = '`';
		tokstr[1] = token;
		tokstr[2] = '\'';
		tokstr[3] = 0;
	}
	msg = ft_strjoin(get_error_msg(SYN_ERR), tokstr);
	free(tokstr);
	return (msg);
}

char	check_line(char *line)
{
	char	c;

	c = ft_isrep(line, "<>;|");
	if (c)
		return (c);
	if (ft_strchr(";|", line[0]))
		return (line[0]);
	if (ft_strchr("<>|", line[ft_strlen(line) - 1]))
		return ('\n');
	return (0);
}
