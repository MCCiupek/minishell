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

	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd)
	{
		print_error(NULL, MEM_ERR);
		free(str_dup);
		return (NULL);
	}
	cmd[i] = NULL;
	return (cmd);
}

char	**tokenize(char *str, char *sep, t_cmd *c, int redir)
{
	char	*str_dup;
	char	*tok;
	char	**cmd;
	int		i;
	int		j;

	str_dup = ft_strdup(str);
	i = ft_get_size(str, &tok, sep, redir);
	cmd = init_cmd(i, str_dup);
	if (!cmd)
		return (NULL);
	i = 0;
	tok = ft_strmbtok(str_dup, sep, "\"\'", redir);
	if (*tok)
		cmd[i++] = ft_strdup(tok);
	tok = ft_strmbtok(NULL, sep, "\"\'", redir);
	while (tok)
	{
		if (*tok)
		{
			j = fill_redir(&cmd[i], c, tok);
			if (j < 0)
			{
				free(str_dup);
				return (NULL);
			}
			i += j;
		}
		tok = ft_strmbtok(NULL, sep, "\"\'", redir);
	}
	free(str_dup);
	return (cmd);
}
