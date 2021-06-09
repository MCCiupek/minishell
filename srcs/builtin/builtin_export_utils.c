/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:20:53 by lkonig            #+#    #+#             */
/*   Updated: 2021/06/09 14:20:55 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_equal(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	compare_len(int len, char *b)
{
	int		i;

	i = 0;
	while (b[i] && b[i] != '=')
		i++;
	if (len != i)
		return (0);
	return (1);
}

void	check_space(void *s)
{
	if (!contains_equal(s))
		ft_strlcat(s, "=\0", ft_strlen(s) + 2);
}
