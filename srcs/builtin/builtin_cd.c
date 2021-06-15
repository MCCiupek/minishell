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

int	built_in_cd_nbargs(char **built_in, t_list *env)
{
	int	i;

	i = 1;
	while (built_in[i])
	{
		if (i >= 2)
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", STDERROR);
			return (1);
		}
		i++;
	}
	return (built_in_cd(built_in[1], env));
}

char	*get_prevdir(t_list *env)
{
	char	*path;

	path = NULL;
	path = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	return (path);
}

int	print_error_cd(char *s, int i)
{
	ft_putstr_fd("minishell: cd: ", STDERROR);
	ft_putstr_fd(s, STDERROR);
	if (i == 1)
		ft_putstr_fd(": No such file or directory\n", STDERROR);
	if (i == 2)
		ft_putstr_fd(" not set\n", STDERROR);
	return (1);
}

int	update_vars(t_list *env, char *pwd)
{
	char	*pwd_ptr;
	char	*tmp;

	if (get_env_var("OLDPWD=", env))
		unset_env(&env, "OLDPWD");
	tmp = ft_strjoin("OLDPWD=", pwd);
	export_new_element(env, tmp);
	free(tmp);
	pwd_ptr = get_pwd();
	unset_env(&env, "PWD");
	tmp = ft_strjoin("PWD=", pwd_ptr);
	export_new_element(env, tmp);
	free(tmp);
	free(pwd_ptr);
	return (0);
}

int	built_in_cd(char *path, t_list *env)
{
	char	*pwd;
	int		ret;

	if (path == NULL)
	{
		if (!get_env_var("HOME=", env))
			return (print_error_cd("HOME", 2));
		path = ft_strrchr(get_env_var("HOME=", env), '=') + 1;
	}
	if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		if (!get_env_var("OLDPWD=", env))
			return (print_error_cd("OLDPWD", 2));
		path = get_prevdir(env);
	}
	pwd = get_pwd();
	if (!get_env_var("PWD=", env))
		export_new_element(env, ft_strjoin("PWD=", pwd));
	if (chdir(path) == 0)
		ret = update_vars(env, pwd);
	else
		ret = print_error_cd(path, 1);
	free(pwd);
	return (ret);
}
