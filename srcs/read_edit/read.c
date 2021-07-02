/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:12:33 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/05 14:12:34 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pos(t_pos *pos)
{
	pos->line = 0;
	pos->hist = 0;
	pos->curs = 0;
}

static char	*free_and_ret_null(char *line)
{
	free(line);
	return (NULL);
}

static int	is_nl(char *buf, char *line)
{
	return (!ft_strncmp(buf, CTRL_C, 1)
		|| (!line[0] && !ft_strncmp(buf, "\n", 1)));
}

static char	*fill_line(char *line, t_list *hist, t_list *env)
{
	char	buf[6];
	t_pos	pos;
	int		r;

	buf[0] = '\0';
	init_pos(&pos);
	while (buf[0] != '\n')
	{
		r = read(STDIN_FILENO, buf, 5);
		buf[r] = '\0';
		if (buf[0] == 127)
			line = delete_backspace(&pos, line);
		else if (is_arrow(buf))
			handle_arrows(buf, &line, &pos, hist);
		else if (is_nl(buf, line))
			return (free_and_ret_null(line));
		else if (!ft_strncmp(buf, CTRL_D, 1) && !line[0])
		{
			free(line);
			builtin_exit(NULL, env, hist);
		}
		else if (r > 0)
			line = ft_display(r, buf[0], &pos, line);
	}
	return (line);
}

char	*read_line(t_list *hist, t_list *env)
{
	char	*line;

	line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	line[0] = '\0';
	if (!line)
	{
		perror("malloc failed");
		return (line);
	}
	line = fill_line(line, hist, env);
	write(STDOUT_FILENO, "\n", 1);
	return (line);
}
