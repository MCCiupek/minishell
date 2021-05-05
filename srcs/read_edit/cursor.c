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

static char	**split_cursor_val(const char *s)
{
	int		k;
	char	**new;

	k = 0;
	while (*(s + k) && (*(s + k) == 27 || *(s + k) == '['))
		k++;
	new = ft_split((s + k), ';');
	return (new);
}

void		get_current_cursor(int *i, int *j)
{
	char	buf[16];
	char	**sp_buf;

	ft_bzero(&buf, 16);
	write(1, "\033[6n", ft_strlen("\033[6n"));
	read(1, &buf, 16);
	sp_buf = split_cursor_val(buf);
	*i = ft_atoi(sp_buf[0]) - 1;
	*j = ft_atoi(sp_buf[1]) - 1;
	free(sp_buf[0]);
	sp_buf[0] = NULL;
	free(sp_buf[1]);
	sp_buf[1] = NULL;
	free(sp_buf);
}

void		cursorleft(int *pos)
{
	int		i;
	int		j;
//	char	*buf;

	if (*pos > 0)
	{
		*pos = *pos - 1;
//		buf = malloc(2048);
		get_current_cursor(&i, &j);
		tgetent(NULL, getenv("TERM"));
		tputs(tgoto(tgetstr("cm", NULL), j - 1, i), 1, ft_putchar);
//		free(buf);
	}
}

void		cursorright(int *pos, int max_pos)
{
	if (*pos < max_pos)
	{
		*pos = *pos + 1;
		tputs(tgetstr("nd", NULL), 1, ft_putchar);
	}
}
