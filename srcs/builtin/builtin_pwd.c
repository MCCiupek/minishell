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
	{
		perror("malloc failed");
		return (NULL);
	}
	if (!(getcwd(cwd, PATH_MAX)))
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

void	built_in_pwd(void)
{
	char	*cwd;

	cwd = get_pwd();
	printf("%s\n", cwd);
	free(cwd);
}
