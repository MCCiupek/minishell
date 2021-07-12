/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:31:26 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/12 18:31:27 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_len(char *s, int k)
{
	int	i;

	i = 0;
	while (s[i] && i < k)
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
}

char	*copy_begin(char *s, int k)
{
	char	*ret;

	ret = malloc(sizeof(char) * k + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, k);
	ret[k] = '\0';
	return (ret);
}

int	print_envvar(char *s, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, s + 1, ft_strlen(s) - 1) == 0)
		{
			ft_putstr_fd((char *)tmp->content + (ft_strlen(s)), 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	echo_env(char *s, t_list *env)
{
	print_envvar(s, env);
}

int	is_n(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (0);
	while (s[i])
		if (s[i++] != 'n')
			return (0);
	return (1);
}
