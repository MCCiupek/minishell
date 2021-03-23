#include "minishell.h"

static void	ft_clean_args(char **cmd)
{
	size_t	i;
	char	*tmp;

	i = 1;
	while (i < ft_arraysize(cmd))
	{
		tmp = ft_strtrim(cmd[i], "\"\'");
		free(cmd[i]);
		cmd[i++] = tmp;
	}
}

void		parse_cmd(char *line, t_list **cmds)
{
	char	**tab;
	char	**cmd;
	int		n_elem;
	int		i;

	i = 0;
	tab = ft_split(line, ';');
	n_elem = ft_arraysize(tab);
	while (i < n_elem)
	{
		cmd = ft_split(tab[i++], ' ');
		ft_lstadd_back(cmds, ft_lstnew(cmd));
	}
}

char	*ft_strtok(char *str, char *limit)
{
	char		*ret;
	static char	*keep;
	int		i;
	int		j;

	i = 0;
	ret = NULL;
	if (str != NULL)
		keep = str;
	if (keep == NULL)
		return(ret);
	while (keep[i])
	{
		j = 0;
		while(limit[j])
		{
			if (keep[i] == limit[j])
				break;
			j++;
		}
		if (keep[i] == limit[j])
			break;
		i++;
	}
	if (keep[0] != '\0')
	{
		ret = ft_substr(keep, 0, i);
		keep = keep + i;
	}
	else
		keep = NULL;
	return (ret);
}


//static char **parsing(vod)


/*int	main(int argc, char **argv)
{
	char	*ptr;
	
	(void)argc;
	(void)argv;
	ptr = ft_strtok("Bonjour le monde", " \n\t\0");
	while (ptr != NULL) 
	{
	//	printf("le token vaut : |%s|\n", ptr);
		ptr = ft_strtok(NULL, " \n\t");
	}
	return (0);
}*/
