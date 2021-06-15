/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 18:59:48 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/12 18:59:49 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_format(char *str)
{
	int	eq_count;
	int	i;

	eq_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			eq_count++;
		i++;
	}
	if (eq_count < 1)
		return (0);
	return (1);
}

int	built_in_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (check_format((char *)tmp->content))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (0);
}
