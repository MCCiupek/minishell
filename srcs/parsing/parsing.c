#include "minishell.h"

char *ft_strmbtok(char *str, char *sep, char *quotes) 
{
    static char *token;
    char *lead;
    char *block;
    int i;
    int j;

	i = 0;
	j = 0;
    if (str)
	{
        token = str;
        lead = str;
    }
    else 
	{
        lead = token;
        if (!*token)
            lead = NULL;
    }
    while (*token) 
	{
        if (i) 
		{
            if (quotes[j] == *token) 
                i = 0;
            token++;
            continue;
        }
        if ((block = ft_strchr(quotes, *token))) 
		{
            i = 1;
            j = block - quotes;
            token++;
            continue;
        }
        if (ft_strchr(sep, *token)) 
		{
            *token = '\0';
            token++;
            break;
        }
        token++;
    }
    return (lead);
}

char **test_strmbtok(char *str, char *sep)
{
	char	*str_dup;
    char	*tok;
	char	**cmd;
	int	i;
    
	i = 0;
	str_dup = ft_strdup(str);
    tok = ft_strmbtok(str, sep, "\"\'");
	if (*tok)
		i++;
    while ((tok = ft_strmbtok(NULL, sep, "\"\'")))
		if (*tok)
			i++;
	cmd = (char **)malloc(sizeof(char *) * i + 1);
	cmd[i] = 0;
	i = 0;
	tok = ft_strmbtok(str_dup, sep, "\"\'");
	if (*tok)
		cmd[i++] = ft_strtrim(tok, "\"\'");
	while ((tok = ft_strmbtok(NULL, sep, "\"\'")))
		if (*tok)
			cmd[i++] = ft_strtrim(tok, "\"\'");
    return (cmd);
}

void		parse_cmd(char *line, t_cmds *cmds)
{
	t_cmd	cmd;
	char	**lines;
	size_t	i;

	i = 0;
	lines = test_strmbtok(line, ";");
	while (i < ft_arraysize(lines))
	{
		cmd.cmd = test_strmbtok(lines[i++], " \t\n");
		ft_lstadd_back(&cmds->cmds, ft_lstnew(&cmd));
	}
}

/*static char *ft_strip_quotes(char *str)
{
	int		len;
	int		i;
	char	*in_quotes;
	char	c;

	i = 0;
	in_quotes = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i])
	{
		in_quotes[i] = '0';
		if (str[i] == '\"' || str[i] == '\'')
		{
			c = str[i];
			str[i] = '\0';
			in_quotes[i] = '\0';
			while (str[i] && str[i] != c)
				in_quotes[i++] = c;
			str[i] = '\0';
			in_quotes[i] = '\0';
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (NULL);
}

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

int	test_strtok(char *s)
{
	char	*ptr;
	
	ptr = ft_strtok(s, "\"");
	while (ptr != NULL)
	{
		printf("le token vaut : |%s|\n", ptr);
		ptr = strtok(NULL, "\"");
	}
	return (0);
}
*/