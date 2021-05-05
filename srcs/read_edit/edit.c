/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:25:29 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/04 19:25:31 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

int			ft_putchar(int n)
{
	char	c;

	c = (char)n;
	write(1, &c, 1);
	return (1);
}

void		delete_to_replace(int i)
{
	char	*buf;
	int		ret;

	buf = malloc(2048);
	while (i > 0)
	{
		i--;
		ret = tgetent(buf, getenv("TERM"));
		tputs(tgetstr("le", NULL), 1, ft_putchar);
		tputs(tgetstr("dc", NULL), 1, ft_putchar);
	}
	free(buf);
}

char		*update_line_end(char *line)
{
	int len;

	len = ft_strlen(line);
	line[len - 1] = '\0';
	return (line);
}

char		*update_line_mid(char *line, t_pos *pos)
{
	char	*end;
	char	*begin;

	begin = cp_begin_str(pos, line);
	end = ft_strdup(line + pos->curs + 1);
	free(line);
	line = ft_strjoin(begin, end);
	free(begin);
	free(end);
	return (line);
}

char		*delete_backspace(t_pos *pos, char *line)
{
//	char	*buf;
	int		ret;

	if (pos->curs > 0)
	{
		if (pos->line > 0)
		{
//			buf = malloc(2048);
			ret = tgetent(NULL, getenv("TERM"));
			tputs(tgetstr("le", NULL), 1, ft_putchar);
			tputs(tgetstr("dc", NULL), 1, ft_putchar);
		//	free(buf);
		}
		if (pos->curs == pos->line)
		{
			line = update_line_end(line);
			pos->curs--;
		}
		else if (pos->curs < pos->line)
		{
			pos->curs--;
			line = update_line_mid(line, pos);
		}
		pos->line--;
	}
	return (line);
}

void		insert_char(char c)
{
	char	*buf;

	buf = malloc(2048);
	tgetent(NULL, getenv("TERM"));
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	tputs(tgetstr("im", NULL), 1, ft_putchar);
	tputs(tgetstr("ic", NULL), 1, ft_putchar);
	ft_putchar((int)c);
	tputs(tgetstr("ei", NULL), 1, ft_putchar);
	tputs(tgetstr("rc", NULL), 1, ft_putchar);
	tputs(tgetstr("nd", NULL), 1, ft_putchar);
	free(buf);
}
