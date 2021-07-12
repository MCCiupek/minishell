/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_sep_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:35:29 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/12 18:35:30 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_quotepos(t_quotepos *pos)
{
	pos->in_quote = 0;
	pos->nb_open = 0;
	pos->nb_close = 0;
	pos->out_quote = 0;
	pos->quote_pos_open = -1;
	pos->is_env = 0;
	pos->quote_pos_close = -1;
}

void	update_openquote(t_quotepos *pos, int k)
{
	if (pos->quote_pos_open == -1)
		pos->quote_pos_open = k;
	pos->nb_open++;
}

void	update_closequote(t_quotepos *pos, int k)
{
	pos->quote_pos_close = k;
	pos->nb_close++;
}

void	update_content(t_quotepos *pos)
{
	if (pos->quote_pos_open == -1 || pos->quote_pos_close > -1)
		pos->out_quote = 1;
	else
		pos->in_quote = 1;
}

int	is_outside(t_quotepos pos)
{
	if (pos.out_quote == 1 && pos.in_quote == 1 && pos.is_env == 1)
		return (pos.quote_pos_open);
	return (-1);
}
