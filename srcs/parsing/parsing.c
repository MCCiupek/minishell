/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strmbtok(char *str, char *sep, char *quotes, int redir) 
{
    static char	*token;
    char		*lead;
    char		*block;
	char		c;
    int			i;
    int			j;

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
		if (!i && redir)
		{
			if (ft_strchr("<>", *token))
			{
				c = *token;
				i = -1;
				token++;
				if (c == '>' && *token == c)
					token++;
				while (ft_strchr(sep, *token))
            		token++;
				continue ;
			}
		}
        if (i == 1) 
		{
            if (quotes[j] == *token) 
                i = 0;
            token++;
            continue ;
        }
        if ((block = ft_strchr(quotes, *token))) 
		{
            i = 1;
            j = block - quotes;
            token++;
            continue ;
        }
        if (ft_strchr(sep, *token)) 
		{
            *token = '\0';
            token++;
            break ;
        }
        token++;
    }
    return (lead);
}

static char **tokenize(char *str, char *sep, t_cmd *c, int redir)
{
	char	*str_dup;
    char	*tok;
	char	**cmd;
	int	i;
    
	i = 0;
	str_dup = ft_strdup(str);
    tok = ft_strmbtok(str, sep, "\"\'", redir);
	if (*tok)
		i++;
    while ((tok = ft_strmbtok(NULL, sep, "\"\'", redir)))
		if (*tok && *tok != '<' && *tok != '>')
			i++;
	cmd = (char **)malloc(sizeof(char *) * i + 1);
	cmd[i] = 0;
	i = 0;
	tok = ft_strmbtok(str_dup, sep, "\"\'", redir);
	if (*tok)
		cmd[i++] = ft_strtrim(tok, "\"\'");
	while ((tok = ft_strmbtok(NULL, sep, "\"\'", redir)))
		if (*tok)
		{
			if (c)
			{
				if (*tok == '<')
					c->in = ft_strtrim(tok, " \t\n<\"\'");
				else if (*tok == '>')
				{
					if (*(tok + 1) == '>')
						c->out_flags = O_WRONLY|O_CREAT|O_APPEND;
					c->out = ft_strtrim(tok, " \t\n>\"\'");
				}
				else
					cmd[i++] = ft_strtrim(tok, "\"\'");
			}
			else
				cmd[i++] = ft_strtrim(tok, "\"\'");
		}
    return (cmd);
}

void		parse_cmd(char *line, t_cmds *cmds)
{
	t_cmd	*cmd_general;
	char	**lines;
	size_t	i;

	i = 0;
	lines = tokenize(line, ";", NULL, 0);
	while (i < ft_arraysize(lines))
	{
		cmd_general = (t_cmd *)malloc(sizeof(t_cmd));
		cmd_general->in = NULL;
		cmd_general->out = NULL;
		cmd_general->out_flags = O_WRONLY|O_CREAT|O_TRUNC;
		cmd_general->cmd = tokenize(lines[i++], " \t\n", cmd_general, 1);
		ft_lstadd_back(&cmds->cmds, ft_lstnew(cmd_general));
	}
}
