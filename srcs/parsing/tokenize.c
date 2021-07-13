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

static int	ft_get_size(char *str, char **tok, char *sep, int redir)
{
	int	size;

	size = 0;
	*tok = ft_strmbtok(str, sep, "\"\'", redir);
	if (**tok)
		size++;
	*tok = ft_strmbtok(NULL, sep, "\"\'", redir);
	while (*tok)
	{
		if (**tok && **tok != '<' && **tok != '>')
			size++;
		*tok = ft_strmbtok(NULL, sep, "\"\'", redir);
	}
	return (size);
}

static char	**init_cmd(int i, char *str_dup)
{
	char	**cmd;
	int		k;

	k = 0;
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	while (k < i)
	{
		cmd[k] = NULL;
		k++;
	}
	if (!cmd)
	{
		print_error(NULL, MEM_ERR);
		free(str_dup);
		return (NULL);
	}
	cmd[i] = NULL;
	return (cmd);
}

static int	ft_count(char **cmd, char *tok, t_cmd *c, int i)
{
	int		j;

	if (*tok)
	{
		j = fill_redir(&cmd[i], c, tok);
		if (j < 0)
			return (-1);
		i += j;
	}
	return (i);
}

static char	**ft_free(char **cmd, t_cmd *c, char *str_dup)
{
	free_array(cmd);
	if (c->in)
		free(c->in);
	if (c->out)
		free(c->out);
	free(str_dup);
	return (NULL);
}

char	**tokenize(char *str, char *sep, t_cmd *c, int redir)
{
	char	*str_dup;
	char	*tok;
	char	**cmd;
	int		i;

	str_dup = ft_strdup(str);
	i = ft_get_size(str, &tok, sep, redir);
	cmd = init_cmd(i, str_dup);
	if (!cmd)
		return (NULL);
	i = 0;
	tok = ft_strmbtok(str_dup, sep, "\"\'", redir);
	if (*tok && !ft_strchr("<>", tok[0]))
		cmd[i++] = ft_strdup(tok);
	if (!ft_strchr("<>", tok[0]))
		tok = ft_strmbtok(NULL, sep, "\"\'", redir);
	while (tok)
	{
		if (ft_count(cmd, tok, c, i) < 0)
			return (ft_free(cmd, c, str_dup));
		i = ft_count(cmd, tok, c, i);
		tok = ft_strmbtok(NULL, sep, "\"\'", redir);
	}
	free(str_dup);
	return (cmd);
}
