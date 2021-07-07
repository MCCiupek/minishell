/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:27:57 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:27:59 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_free_str(char *str)
{
	free(str);
	return (NULL);
}

static char	*get_path(t_list *env)
{
	t_list	*tmp;
	char	*path;

	tmp = env;
	path = NULL;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, "PATH=", 5))
		{
			path = ft_strdup(&((char *)tmp->content)[5]);
			break ;
		}
		tmp = tmp->next;
	}
	return (path);
}

static char	*get_bin(char **cmd, char **path_split)
{
	int		i;
	char	*bin;

	i = 0;
	bin = NULL;
	while (path_split[i])
	{
		bin = (char *)ft_calloc(sizeof(char), \
			(ft_strlen(path_split[i]) + ft_strlen(cmd[0]) + 2));
		if (!bin)
			break ;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd[0]);
		if (!access(bin, F_OK))
			break ;
		bin = ft_free_str(bin);
		i++;
	}
	return (bin);
}

int	get_absolute_path(char **cmd, t_list *env)
{
	char	*path;
	char	*bin;
	char	**path_split;
	char	*dup;

	path = NULL;
	bin = NULL;
	path_split = NULL;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) && ft_strncmp(cmd[0], "..", 2))
	{
		dup = ft_strdup(cmd[0]);
		path = get_path(env);
		if (!path)
			error(PATH_ERR);
		path_split = ft_split(path, ':');
		path = ft_free_str(path);
		bin = get_bin(cmd, path_split);
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = dup;
		if (bin)
			cmd[0] = bin;
		return (bin != NULL);
	}
	return (1);
}
