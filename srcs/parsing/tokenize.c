/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_redir(char *redir, int *flags, char *tok, char *str_dup)
{
	int	fd;
	int	mode;

	mode = READ;
	if (flags)
		mode = WRITE;
	if (redir)
		free(redir);
	if (mode == WRITE && *(tok + 1) == '>')
		*flags = O_WRONLY | O_CREAT | O_APPEND;
	if (mode == READ)
		redir = ft_strtrim(tok, " \t\n<\"\'");
	else
		redir = ft_strtrim(tok, " \t\n>\"\'");
	if ((mode == READ && (fd = open(redir, O_RDONLY)) < 0) ||
		(mode == WRITE && (fd = open(redir, *flags, 0644)) < 0))
	{
		perror("Couldn't open file");
		free(str_dup);
		return (NULL);
	}
	close(fd);
	return (redir);
}

static int	ft_get_size(char *str, char **tok, char *sep, int redir)
{
	int	size;

	size = 0;
	*tok = ft_strmbtok(str, sep, "\"\'", redir);
	if (**tok)
		size++;
	while ((*tok = ft_strmbtok(NULL, sep, "\"\'", redir)))
		if (**tok && **tok != '<' && **tok != '>')
			size++;
	return (size);
}

static int	fill_redir(char **cmd, t_cmd *c, char *tok, char *str_dup)
{
	if (c)
		if (*tok == '<')
			c->in = ft_redir(c->in, NULL, tok, str_dup);
		else if (*tok == '>')
			c->out = ft_redir(c->out, &c->out_flags, tok, str_dup);
		else
		{
			*cmd = ft_strdup(tok);
			return (1);
		}
	else
	{
		*cmd = ft_strdup(tok);
		return (1);
	}
	return (0);
}

char		**tokenize(char *str, char *sep, t_cmd *c, int redir)
{
	char	*str_dup;
	char	*tok;
	char	**cmd;
	int		i;

	str_dup = ft_strdup(str);
	i = ft_get_size(str, &tok, sep, redir);
	if (!(cmd = (char **)malloc(sizeof(char *) * (i + 1))))
	{
		perror("malloc failed");
		free(str_dup);
		return (NULL);
	}
	cmd[i] = NULL;
	i = 0;
	tok = ft_strmbtok(str_dup, sep, "\"\'", redir);
	if (*tok)
		cmd[i++] = ft_strdup(tok);
	while ((tok = ft_strmbtok(NULL, sep, "\"\'", redir)))
		if (*tok)
			i += fill_redir(&cmd[i], c, tok, str_dup);
	free(str_dup);
	return (cmd);
}
