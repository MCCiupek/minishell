#include "minishell.h"

void	built_in_cd(char *path)
{
	if (chdir(path) == -1)
		exit(EXIT_FAILURE);
}

void	built_in_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		exit(EXIT_FAILURE);;
}

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
	if(ft_strncmp(built_in[0], "pwd", 3) == 0)
		built_in_pwd();
	else if (!ft_strncmp(built_in[0], "cd", 2))
		built_in_cd(built_in[1]);
//	else if (!ft_strncmp(built_in[0], "export", 6)   A suivre sur le meme principe
}
