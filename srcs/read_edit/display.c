/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:12:33 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/05 14:12:34 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cp_begin_str(t_pos *pos, char *line)
{
	int		i;
	char	*begin;

	i = 0;
	begin = NULL;
	begin = (char *)malloc(sizeof(char *) * (pos->curs + 1));
	if (!begin)
		return (NULL);
	ft_strlcpy(begin, line, pos->curs + 1);
	begin[pos->curs] = '\0';
	return (begin);
}

static void	display_char_end(char c, t_pos *pos, char *line)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	line[pos->line] = c;
	pos->line++;
	pos->curs++;
	line[pos->line] = '\0';
}

static char	*display_char_mid(char c, t_pos *pos, char *line)
{
	char	*end;
	char	*begin;
	char	*tmp;
	char	mid[2];
	int		to_store;

	mid[0] = c;
	mid[1] = '\0';
	to_store = pos->line - pos->curs;
	end = ft_strdup(line + pos->curs);
	begin = cp_begin_str(pos, line);
	insert_char(c);
	tmp = ft_strjoin(begin, mid);
	free(line);
	line = ft_strjoin(tmp, end);
	pos->line = ft_strlen(line);
	pos->curs++;
	free(tmp);
	free(begin);
	free(end);
	return (line);
}

char	*ft_display(int r, char buf_0, t_pos *pos, char *line)
{
	if (r == 1 && buf_0 != '\n' && buf_0 != '\034' && (ft_isprint(buf_0) || buf_0 == 9))
	{
		if (pos->curs == pos->line)
			display_char_end(buf_0, pos, line);
		else if (pos->curs < pos->line)
			line = display_char_mid(buf_0, pos, line);
	}
	return (line);
}
