/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:24:19 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/12 14:24:24 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*jf(char *s, char *replacement, char *copy, int i)
{
	char	*copy_tmp;

	copy_tmp = ft_strjoin(copy, replacement);
	free(copy);
	copy = ft_strjoin(copy_tmp, ft_strnchr(&s[i] + 1, " \\/=$"));
	free(copy_tmp);
	free(s);
	return (copy);
}

static char	*get_num(int n, char *s, char *copy, int i)
{
	char	*res;
	char	*num;

	num = ft_itoa(n);
	res = jf(s, num, copy, i);
	free(num);
	return (res);
}

static char	*final_join(char *copy, char *s, int i)
{
	char	*copy_tmp;

	copy_tmp = ft_strjoin(copy, ft_strnchr(&s[i] + 1, " \\/=$"));
	free(copy);
	free(s);
	return (copy_tmp);
}

int	is_in_env(char *s, t_list *env, int i)
{
	t_list	*tmp;

	tmp = env;
	if (s)
	{
		while (tmp)
		{
			if (!ft_strncmp((char *)tmp->content, &s[i] + 1,
					ft_locnchr(&s[i] + 1, " \\/=$") - 1))
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

char	*replace(char *s, int i, t_list *env, int err)
{
	t_list	*tmp;
	char	*cp;

	tmp = env;
	if (s)
	{
		cp = (char *)malloc(sizeof(s) * (i + 1));
		if (!cp)
			return (NULL);
		ft_strlcpy(cp, s, i + 1);
		if (!ft_strncmp("?", &s[i] + 1, ft_locnchr(&s[i] + 1, " \\/=$") - 1))
			return (get_num(err, s, cp, i));
		if (!ft_strncmp("$", &s[i] + 1, ft_locnchr(&s[i] + 1, " \\/=$") - 1))
			return (get_num(g_pid, s, cp, i));
		while (tmp)
		{
			if (!ft_strncmp((char *)tmp->content, &s[i] + 1,
					ft_locnchr(&s[i] + 1, " \\/=$") - 1))
				return (jf(s, ft_strchr((char *)tmp->content, '=') + 1, cp, i));
			tmp = tmp->next;
		}
		return (final_join(cp, s, i));
	}
	return (s);
}
