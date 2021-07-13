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

static char	ft_next(int empty, char c, char next, char s)
{
	if (ft_strchr(" \t", c) && empty)
		return (next);
	if (ft_strchr("<>;|", c))
		return (s);
	return (0);
}

static char	ft_isrep(char *str, char *sep)
{
	int		i;
	int		empty;
	char	c;
	int		quote;
	char	next;

	init(&i, &empty, &quote);
	while (++i < ft_strlen(str) - 1)
	{
		empty = ft_isempty(&c, &next, str[i], sep);
		if (ft_strchr(sep, str[i]) || ft_strchr(" \t", str[i]))
			c = str[i];
		if (ft_strchr("\"\'", str[i]) || (str[i] == quote && quote))
			quote = ft_isquote(str[i], quote);
		else if (c && !quote && !(i > 0 && str[i - 1] == '\\'))
		{
			if (c == '>' && str[i + 1] && str[i + 1] == c && str[i + 2] != c)
				continue ;
			next = ft_spc(&str[i + 1]);
			if (!next || ft_strchr(sep, next))
				return (ft_next(empty, c, next, str[i]));
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
	if (ft_strchr("<>|", line[ft_strlen(line) - 1]) && \
		(ft_strlen(line) - 2 >= 0 && line[ft_strlen(line) - 2] != '\\'))
		return ('\n');
	return (0);
}
