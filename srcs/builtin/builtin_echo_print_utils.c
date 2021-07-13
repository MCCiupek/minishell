/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_print_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:52:13 by mciupek           #+#    #+#             */
/*   Updated: 2021/07/13 20:52:14 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_env_var(char *s, int *len_var, t_list *env)
{
	char	*res;
	t_list	*tmp;

	tmp = env;
	if (s)
	{
		if (s[1] == '?')
			return (ft_itoa(g_gbl.exit));
		if (s[1] == '$')
			return (ft_itoa(g_gbl.pid));
		res = ft_find_in_env(&s[1], tmp, len_var);
		if (res)
			return (ft_strdup(res));
	}
	return (NULL);
}

int	get_len(char *s)
{
	int	len_var;

	len_var = ft_locnchr(&s[1], " \\/=$\"\'");
	if (s[1] == '$')
		len_var = 1;
	return (len_var);
}
