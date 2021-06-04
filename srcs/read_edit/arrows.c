/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:12:33 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/05 14:12:34 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_up(char *line, t_pos *pos, t_list *hist)
{
	free(line);
	return (access_history('u', pos, hist));
}

static char	*ft_down(char *line, t_pos *pos, t_list *hist)
{
	free(line);
	return (access_history('d', pos, hist));
}

void	handle_arrows(char *buf, char **line, t_pos *pos, t_list *hist)
{
	if (!ft_strncmp(buf, UP, 4))
		*line = ft_up(*line, pos, hist);
	else if (!ft_strncmp(buf, DOWN, 4))
		*line = ft_down(*line, pos, hist);
	else if (!ft_strncmp(buf, RIGHT, 4))
		cursorright(&pos->curs, pos->line);
	else if (!ft_strncmp(buf, LEFT, 4))
		cursorleft(&pos->curs);
}

int	is_arrow(char *buf)
{
	return (!ft_strncmp(buf, UP, 4) || !ft_strncmp(buf, DOWN, 4)
		|| !ft_strncmp(buf, RIGHT, 4) || !ft_strncmp(buf, LEFT, 4));
}
