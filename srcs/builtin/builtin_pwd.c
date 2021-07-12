/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:00:02 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/12 19:00:03 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	char	*cwd;

	cwd = (char *)calloc(sizeof(char), PATH_MAX + 1);
	if (!cwd)
		return (NULL);
	if (!(getcwd(cwd, PATH_MAX)))
	{
		free(cwd);
		return (NULL);
	}
	return (cwd);
}

char	*get_pwd_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PWD=", 4))
		{
			if (!(tmp->content + 4))
				return (".");
			else
				return (tmp->content + 4);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	built_in_pwd(void)
{
	char	*cwd;

	cwd = get_pwd();
	if (!cwd)
	{
		perror("getcwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
