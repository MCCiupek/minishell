/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:53:31 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:53:34 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parent_env	ft_parent_env(void)
{
	t_parent_env	env;

	env.path = getenv("PATH");
	env.home = getenv("HOME");
	env.oldpwd = getenv("OLDPWD");
	env.pwd = getenv("PWD");
	env.shlvl = getenv("SHLVL");
	return (env);
}

void	add_env_var(t_list **env, char *var)
{
	char			*alloc;
	t_parent_env	envp;

	envp = ft_parent_env();
	alloc = NULL;
	if (!ft_strncmp(var, "HOME", 4))
	{
		alloc = ft_strjoin("HOME=", envp.path);
		if (!alloc)
			error(MEM_ERR);
	}
	else if (!ft_strncmp(var, "PATH", 4))
	{
		alloc = ft_strdup("PATH=/bin:/usr/bin");
		if (!alloc)
			error(MEM_ERR);
	}
	else if (!ft_strncmp(var, "OLDPWD", 6))
	{
		alloc = ft_strdup("OLDPWD=");
		if (!alloc)
			error(MEM_ERR);
	}
	ft_lstadd_back(env, ft_lstnew(alloc));
	return ;
}

t_list	*dup_env(char **envp)
{
	int			i;
	const char	*var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	t_list		*first;

	first = NULL;
	i = -1;
	while (envp[++i])
	{
		ft_lstadd_back(&first, ft_lstnew(ft_strdup(envp[i])));
		if (!ft_strncmp(envp[i], "PATH", 4))
			var_lst[0] = NULL;
		else if (!ft_strncmp(envp[i], "HOME", 4))
			var_lst[1] = NULL;
		else if (!ft_strncmp(envp[i], "OLDPWD", 6))
			var_lst[2] = NULL;
		else if (!ft_strncmp(envp[i], "PWD", 3))
			var_lst[3] = NULL;
		else if (!ft_strncmp(envp[i], "SHLVL", 5))
			var_lst[4] = NULL;
	}
	i = -1;
	while (++i < 5)
		if (var_lst[i] != NULL)
			add_env_var(&first, (char *)var_lst[i]);
	return (first);
}

char	*get_env_var(char *var, t_list *env)
{
	t_list	*tmp;
	int		len;
	int		len_tocmp;

	len = ft_strlen(var);
	tmp = env;
	while (tmp)
	{
		len_tocmp = 0;
		while (((char *)tmp->content)[len_tocmp] && ((char *)tmp->content)[len_tocmp] != '=')
			len_tocmp++;
		if (!(ft_strncmp(var, (char *)tmp->content, len))
			&& len == len_tocmp + 1)
			return (tmp->content);
		tmp = tmp->next;
	}
	printf("\n");
	return (NULL);
}
