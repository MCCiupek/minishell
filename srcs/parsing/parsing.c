#include "minishell.h"

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
