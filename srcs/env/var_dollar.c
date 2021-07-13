/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 16:30:09 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/13 16:30:10 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	keep_dollar_sign(char **cmd)
{
	int		k;

	k = 0;
	while ((*cmd)[k])
	{
		if ((*cmd)[k] == '\\' && (*cmd)[k + 1] && (*cmd)[k + 1] == '$')
			ft_strlcpy((*cmd) + k, (*cmd) + k + 1, ft_strlen((*cmd)));
		k++;
	}
}

void	replace_dollar_sign(char **cmd, t_infos	*inf)
{
	int		len;
	char	*tmp;

	len = 0;
	tmp = ft_strdup(*cmd);
	free(*cmd);
	(*cmd) = replace(ft_strtrim(tmp, &(inf->c)), inf->i, \
		g_gbl.env, &len);
	if (!is_in_env(tmp, g_gbl.env, inf->i) && inf->i > 0)
		(inf->i)--;
	free(tmp);
}

void	determine_dollar_behavior(int exp, int quote, char **cmd, t_infos *inf)
{
	if (exp == 0 || (exp == 1 && quote == 0))
	{
		if (inf->i == 0 || (*cmd)[inf->i - 1] != '\\')
			replace_dollar_sign(cmd, inf);
		else
			keep_dollar_sign(cmd);
	}
	else
		add_backslash((inf->i)++, cmd);
}
