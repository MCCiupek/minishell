/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_sep.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:33:34 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/12 18:33:35 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	detect_quotes(char *s, t_quotepos *pos, int k)
{
	if ((s[k] == '\'' || s[k] == '\"') && pos->in_quote == 0)
		update_openquote(pos, k);
	else if ((s[k] == '\'' || s[k] == '\"') && pos->in_quote == 1)
	{
		if (k == 0 || s[k - 1] != '\\')
			update_closequote(pos, k);
	}
	else
		update_content(pos);
}

int	is_outside_quote(char *s)
{
	int			k;
	t_quotepos	pos;

	k = 0;
	init_quotepos(&pos);
	while (s[k])
	{
		if (s[k] == '$' && pos.quote_pos_close > -1)
			return (pos.quote_pos_close + 1);
		else if (s[k] == '$' && pos.quote_pos_open > -1)
			pos.is_env = 1;
		else
			detect_quotes(s, &pos, k);
		if (pos.nb_close > pos.nb_open)
			return (k);
		k++;
	}
	return (is_outside(pos));
}
