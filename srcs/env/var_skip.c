/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_skip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:53:32 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/13 15:53:34 by lkonig           ###   ########.fr       */
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

void	skip_in_cmd(char **cmd, t_infos *inf, int skip_quotes, char *quotes)
{
	if (skip_quotes && (*cmd)[inf->i] && !(inf->c) && \
		ft_strchr(quotes, (*cmd)[inf->i]))
		(*cmd) = ft_skip((*cmd), inf->i, 1, &(inf->c));
	if (skip_quotes && ((inf->c) == '\"' || !(inf->c)) && \
		(*cmd)[inf->i] == '\\' && \
		!ft_isalnum((*cmd)[inf->i + 1]))
		(*cmd) = ft_skip((*cmd), (inf->i)++, -1, &(inf->c));
	if (skip_quotes && (inf->c) && (*cmd)[inf->i] == (inf->c))
		(*cmd) = ft_skip((*cmd), inf->i, 0, &(inf->c));
}
