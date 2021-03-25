/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_pwd_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:32:04 by fcivetta          #+#    #+#             */
/*   Updated: 2021/03/25 16:34:45 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_cd(char *path, t_env *env)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	if (path == NULL)
		return;
	if (chdir(path) == 0)
	{
		pwd = ft_strrchr(get_env_var("PWD=", env), '=') + 1;
		oldpwd = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
		if (oldpwd != NULL && pwd != NULL)
			ft_strlcpy(oldpwd, pwd, ft_strlen(pwd));
		if (pwd != NULL)
		{
//			pwd = &pwd[-ft_strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			ft_strlcpy(pwd, pwd_ptr, ft_strlen(pwd_ptr));
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	}
	else
		error(PWD_ERR);
}

char	*built_in_pwd(void)
{
	char	*cwd;
 
//	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=") + 1)))
	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + 1)))
		error(MEM_ERR);
//	ft_strcat(cwd, "PWD=");
//	if(!(getcwd(&cwd[4], PATH_MAX)))
	if(!(getcwd(cwd, PATH_MAX)))
		error(PWD_ERR);
	return(cwd);
}


void	built_in_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}
