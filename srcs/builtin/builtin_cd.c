/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 17:14:05 by mciupek           #+#    #+#             */
/*   Updated: 2021/05/12 17:14:06 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd(void)
{
	char	*cwd;

	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + 1)))
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

void		built_in_cd_nbargs(char **built_in, t_list *env)
{
	int	i;

	i = 1;
	while (built_in[i])
	{
		if (i >= 2)
		{
			ft_putstr_fd("minishell: cd: trop d'arguments\n", STDERROR);
			return ;
		}
		i++;
	}
	built_in_cd(built_in[1], env);
}

char		*get_prevdir(t_list *env)
{
	char	*path;

	path = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	return (path);
}

void		built_in_cd(char *path, t_list *env)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	if (path == NULL)
		path = ft_strrchr(get_env_var("HOME=", env), '=') + 1;
	if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
		path = get_prevdir(env);
	if (chdir(path) == 0)
	{
		pwd = ft_strrchr(get_env_var("PWD=", env), '=') + 1;
		oldpwd = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
		if (oldpwd != NULL && pwd != NULL)
			ft_strlcpy(oldpwd, pwd, ft_strlen(pwd) + 1);
		if (pwd != NULL)
		{
			pwd_ptr = get_pwd();
			ft_strlcpy(pwd, pwd_ptr, ft_strlen(pwd_ptr) + 1);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	}
	else
		error(PWD_ERR);
}
