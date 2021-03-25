#include "minishell.h"

t_parent_env	ft_parent_env(void)
{
	t_parent_env	env;
	
	env.path = getenv("PATH");
	env.home = getenv("HOME");
	env.oldpwd = getenv("OLDPWD");
	env.pwd = getenv("PWD");
	env.shlvl = getenv("SHLVL");
	return(env);
}
/*
int	main(void)
{
	t_parent_env env;

	env = ft_parent_env();
	printf("%s\n", env.path);
	printf("%s\n", env.home);
	printf("%s\n", env.oldpwd);
	printf("%s\n", env.pwd);
	printf("%s\n", env.shlvl);
}

*/

t_env	*add_env_var(char *var)
{
	char		*alloc;
	t_parent_env	env;
	
	env = ft_parent_env();
	if (!strncmp(var, "HOME", 4))
	{
/*		if(!(alloc = (char *)calloc(sizeof(char), ft_strlen(env.path) + ft_strlen("HOME=") + 1)))
			error(MEM_ERR);*/
		if(!(alloc = ft_strjoin("HOME=", env.path))) //Dansle tuto: pw->pw_dir
			error(MEM_ERR);
	}
	else if (!strncmp(var, "PATH", 4))
	{
		if(!(alloc = ft_strdup("PATH=/bin:/usr/bin")))
			error(MEM_ERR);

	}
	else if (!strncmp(var, "OLDPWD", 6))
	{
		if(!(alloc =ft_strdup("OLDPWD=")))
			error(MEM_ERR);
	}
	else if (!strncmp(var, "PWD", 3))
	{

	}
	return(add_tail(alloc));
}

t_env	*dup_env(char **envp)
{
	int	nb_elem;
	int	i;
	char	*var_lst[] = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	t_env	*first;

	nb_elem = 5;
	i = 0;
//	var_lst = {"PATH", "HOME", "OLDPWD", "PWD", "SHLVL", NULL};
	while(envp[i])
	{
		first = add_tail(ft_strdup(envp[i]));
		if(!ft_strncmp(envp[i], "PATH", 4))
			var_lst[0] = NULL;
		else if(!ft_strncmp(envp[i], "HOME", 4))
			var_lst[1] = NULL;
		else if(!ft_strncmp(envp[i], "OLDPWD", 6))
			var_lst[2] = NULL;
		else if(!ft_strncmp(envp[i], "PWD", 3))
			var_lst[3] = NULL;
		else if(!ft_strncmp(envp[i], "SHLVL", 5))
			var_lst[4] = NULL;	
		i++;
	}
	i = 0;
	while (i < 5)
	{
		if(var_lst[i] != NULL)
			first = add_env_var(var_lst[i]);
		i++;
	}
	return (first);
}

//static	t_env *first = NULL;  On peut balancer comme ca ? Non c'est une globale

t_env	*add_tail(char *var)
{
	static	t_env	*first; //set as NULL ?
	t_env 		*ptr;
	t_env		*new_node;

	ptr = first;
	new_node = NULL;
	if(!(new_node = (t_env *)ft_calloc(sizeof(t_env), 1)))
		error(MEM_ERR);
	new_node->var = var;
	new_node->next = NULL; 
	if (ptr == NULL)
		first = new_node;
	else
	{
		while(ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new_node;
	}
	return(first);	
}

char	*get_env_var(char *var, t_env *env)
{
	t_env	*tmp;
	int		len;

	len = ft_strlen(var);
	tmp = env;
	while(tmp != NULL)
	{
		if (!(strncmp(var, tmp->var, len)))
			return(tmp->var);
		tmp = tmp->next;
	}
	return(NULL);
}
