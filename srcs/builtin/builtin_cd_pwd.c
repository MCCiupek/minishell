#include "minishell.h"

void	built_in_cd(char *path)
{
	if (chdir(path) == -1)
		error(CD_ERR);
}

char	*built_in_pwd(void)
{
	char	*cwd;
 
	if (!(cwd = (char *)calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=") + 1)))
		error(MEM_ERR);
	ft_strcat(cwd, "PWD=");
	if(!(getcwd(&cwd[4], PATH_MAX)))
		error(PWD_ERR);
	return(cwd);
}

/*
void	build_in_env(void)
{
	t_env	*tmp;

	tmp 
}*/

int	is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", NULL}; // A mettre dans un tableau dans la structure principale
	int		i;

	i = 0;
	while (built_in[i])
	{
		if(ft_strncmp(cmd, built_in[i], ft_strlen(built_in[i])) == 0)
			return(1);
		i++;
	}
	return (0);
}

void	exec_built_in(char **built_in)
{
	char	*str;
	if(ft_strncmp(built_in[0], "pwd", 3) == 0)
	{
		str = built_in_pwd();
		printf("%s\n", str);
	}
	else if (!ft_strncmp(built_in[0], "cd", 2))
		built_in_cd(built_in[1]);
//	else if (!ft_strncmp(built_in[0], "env", 3))
//		built_in_env();
//	else if (!ft_strncmp(built_in[0], "export", 6)   A suivre sur le meme principe
}
