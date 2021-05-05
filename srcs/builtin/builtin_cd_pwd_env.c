#include "minishell.h"

void	built_in_cd_nbargs(char **built_in, t_list *env)
{
	int	i;

	i = 1;
	while (built_in[i])
	{
		if (i >= 2)
		{
			printf("minishell: cd: trop d'arguments\n");
			return;
		}
		i++;
	}
	built_in_cd(built_in[1], env);
}

static char	*get_pwd(void)
{
	char	*cwd;
 
	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + 1)))
	{
		perror("malloc failed");
		return (NULL);
	}
	if(!(getcwd(cwd, PATH_MAX)))
	{
		perror("getcwd");
		return (NULL);
	}
	return(cwd);
}

void	built_in_cd(char *path, t_list *env)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	if (path == NULL)
		path = ft_strrchr(get_env_var("HOME=", env), '=') + 1;
	if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		path = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
		ft_putstr_fd(path, 1);
		ft_putchar_fd('\n', 1);
	}
	if (chdir(path) == 0)
	{
		pwd = ft_strrchr(get_env_var("PWD=", env), '=') + 1;
		oldpwd = ft_strrchr(get_env_var("OLDPWD=", env), '=') + 1;
		if (oldpwd != NULL && pwd != NULL)
			ft_strlcpy(oldpwd, pwd, ft_strlen(pwd));
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

void	built_in_pwd(void)
{
	char	*cwd;
 
//	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=") + 1)))
//	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + 1)))
//		error(MEM_ERR);
//	ft_strcat(cwd, "PWD=");
//	if(!(getcwd(&cwd[4], PATH_MAX)))
//	if(!(getcwd(cwd, PATH_MAX)))
//		error(PWD_ERR);
	cwd = get_pwd();
	printf("%s\n", cwd);
	free(cwd);
	//return(cwd);
}

int		check_format(char *str)
{
	int	eq_count;
	int	i;

	eq_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			eq_count++;
		i++;
	}
	if (eq_count != 1)
		return (0);
	return (1);
}

void	built_in_env(t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (check_format((char *)tmp->content))
			printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}
