/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_error_fd(char *redir)
{
	if (*redir == '$')
	{
		ft_putstr_fd("minishell: ", STDERROR);
		ft_putstr_fd(redir, STDERROR);
		ft_putstr_fd(" : ambiguous redirect\n", STDERROR);
	}
	else if (errno == 13)
		print_error(redir, NO_RGT);
	else
		print_error(redir, UKN_FD);
	free(redir);
	return (NULL);
}

char	*open_fd(int mode, char *redir, int *flags)
{
	int		fd;

	fd = 0;
	if (ft_strchr(redir, '\\'))
		return (redir);
	if (mode == READ)
		fd = open(redir, O_RDONLY);
	else
	{
		if (*redir == '$')
			fd = open("\0", *flags, 0644);
		else
			fd = open(redir, *flags, 0644);
	}
	if (fd < 0)
		return (ft_error_fd(redir));
	close(fd);
	return (redir);
}

static char	*ft_redir(char *redir, int *flags, char *tok)
{
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
	return (open_fd(mode, redir, flags));
}

static int	get_redir(char *tok, t_cmd *c, char **cmd)
{
	if (!tok)
		return (0);
	if (*tok == '<')
	{
		c->in = ft_redir(c->in, NULL, tok);
		if (!c->in)
			return (-1);
	}
	else if (*tok == '>')
	{
		c->out = ft_redir(c->out, &c->out_flags, tok);
		if (!c->out)
			return (-1);
	}
	else
	{
		if (cmd)
		{
			free(*cmd);
			*cmd = NULL;
		}
		*cmd = ft_strdup(tok);
		return (1);
	}
	return (0);
}

int	fill_redir(char **cmd, t_cmd *c, char *tok)
{
	int		ret;

	if (c)
	{
		ret = get_redir(tok, c, cmd);
		return (ret);
	}
	else
	{
		if (*cmd)
			free(*cmd);
		*cmd = ft_strdup(tok);
		return (1);
	}
	return (0);
}
