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
	copy = ft_strjoin(copy_tmp, ft_strnchr(&s[i] + 1, " \\/=$\"\'"));
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

	copy_tmp = ft_strjoin(copy, ft_strnchr(&s[i] + 1, " \\/=$\"\'"));
	free(copy);
	free(s);
	return (copy_tmp);
}

char	*ft_find_in_env(char *s, t_list *env, int *len_var)
{
	int		len;

	while (env)
	{
		if (!ft_strncmp((char *)env->content, s, ft_locnchr(s, " \\/=$\"\'")))
		{
			len = 0;
			while (((char *)env->content)[len] != '=')
				len++;
			if (!ft_strncmp((char *)env->content, s, len))
			{
				*len_var = ft_strlen(ft_strchr((char *)env->content, '='));
				return (ft_strchr((char *)env->content, '=') + 1);
			}
		}
		env = env->next;
	}
	return (NULL);
}

char	*replace(char *s, int i, t_list *env, int *len_var)
{
	t_list	*tmp;
	char	*cp;
	char	*res;

	tmp = env;
	if (s)
	{
		cp = (char *)malloc(sizeof(s) * (i + 1));
		if (!cp)
			return (NULL);
		ft_strlcpy(cp, s, i + 1);
		if (!ft_strncmp("?", &s[i] + 1, ft_locnchr(&s[i] + 1, " \\/=$\"\'")))
			return (get_num(g_gbl.exit, s, cp, i));
		if (!ft_strncmp("$", &s[i] + 1, ft_locnchr(&s[i] + 1, " \\/=$\"\'")))
			return (get_num(g_gbl.pid, s, cp, i));
		res = ft_find_in_env(&s[i] + 1, tmp, len_var);
		if (res)
			return (jf(s, res, cp, i));
		return (final_join(cp, s, i));
	}
	return (s);
}
