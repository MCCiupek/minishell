/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_cmd(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->out_flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->nb = 0;
	cmd->is_env = 0;
}

int	ft_isempty(char *c, char *next, char s, char *sep)
{
	int		empty;

	*c = 0;
	*next = 0;
	empty = 0;
	if (!ft_strchr(sep, s) && !ft_strchr(" \t", s))
		empty = 0;
	if (ft_strchr(sep, s))
		empty = 1;
	return (empty);
}

char	ft_isquote(char c, int quote)
{
	if (ft_strchr("\"\'", c))
		return (c);
	else if (c == quote && quote)
		return (0);
	return (0);
}

void	init(int *i, int *empty, int *quote)
{
	*i = -1;
	*empty = 1;
	*quote = 0;
}
