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

char		*ft_strmbtok(char *str, char *sep, char *quotes, int redir)
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

static char	**tokenize(char *str, char *sep, t_cmd *c, int redir)
{
	char	*str_dup;
	char	*tok;
	char	**cmd;
	int		i;
	int		fd;

	i = 0;
	str_dup = ft_strdup(str);
	tok = ft_strmbtok(str, sep, "\"\'", redir);
	if (*tok)
		i++;
	while ((tok = ft_strmbtok(NULL, sep, "\"\'", redir)))
		if (*tok && *tok != '<' && *tok != '>')
			i++;
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
		{
			if (c)
			{
				if (*tok == '<')
				{
					if (c->in)
						free(c->in);
					c->in = ft_strtrim(tok, " \t\n<\"\'");
					if ((fd = open(c->in, O_RDONLY)) < 0)
					{
						perror("Couldn't open file");
						free(str_dup);
						return (NULL);
					}
					close(fd);
				}
				else if (*tok == '>')
				{
					if (c->out)
						free(c->out);
					if (*(tok + 1) == '>')
						c->out_flags = O_WRONLY | O_CREAT | O_APPEND;
					c->out = ft_strtrim(tok, " \t\n>\"\'");
					if ((fd = open(c->out, c->out_flags, 0644)) < 0)
					{
						perror("Couldn't open file");
						free(str_dup);
						return (NULL);
					}
					close(fd);
				}
				else
					cmd[i++] = ft_strdup(tok);
			}
			else
				cmd[i++] = ft_strdup(tok);
		}
	free(str_dup);
	return (cmd);
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->out_flags = O_WRONLY | O_CREAT | O_TRUNC;
	cmd->nb = 0;
	cmd->background = 0;
}

int			ft_isrep2(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			if (s[i] && s[i] == c)
				return (1);
	return (0);
}

int			ft_isrep3(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
		if (s[i++] == c)
			if (s[i] && s[i] == c && s[i + 1] && s[i + 1] == c)
				return (1);
	return (0);
}

int			check_line(char *line)
{
	if (!line)
		return (0);
	if (ft_strchr(";|", line[0]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERROR);
		ft_putchar_fd(line[0], STDERROR);
		ft_putstr_fd("'\n", STDERROR);
		return (0);
	}
	if (ft_strchr("<>|", line[ft_strlen(line) - 1]))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERROR);
		return (0);
	}
	if (ft_isrep2(line, '<'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", STDERROR);
		return (0);
	}
	if (ft_isrep2(line, ';'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `;'\n", STDERROR);
		return (0);
	}
	if (ft_isrep2(line, '|'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERROR);
		return (0);
	}
	if (ft_isrep3(line, '>'))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", STDERROR);
		return (0);
	}
	return (1);
}

int			parse_cmd(char *line, t_list **cmds)
{
	t_cmd	*cmd_general;
	t_cmd	*cmd;
	char	**lines;
	char	**pipes;
	char	*dup;
	size_t	i;
	size_t	j;
	size_t	size;

	i = 0;
	if (!line || !check_line(line))
		return (2);
	if (!(lines = tokenize(line, ";", NULL, 0)))
	{
		perror("tokenize");
		return (1);
	}
	while (i < ft_arraysize(lines))
	{
		cmd_general = (t_cmd *)malloc(sizeof(t_cmd));
		init_cmd(cmd_general);
		dup = ft_strdup(lines[i]);
		if (!(cmd_general->cmd = tokenize(dup, " \t\n", cmd_general, 1)))
		{
			free(dup);
			free(cmd_general);
			return (1);
		}
		if (!(pipes = tokenize(lines[i++], "|", NULL, 0)))
		{
			perror("tokenize");
			free(dup);
			free_t_cmd(cmd_general);
			return (1);
		}
		j = 0;
		size = ft_arraysize(pipes);
		while (j < size)
		{
			cmd = (t_cmd *)malloc(sizeof(t_cmd));
			init_cmd(cmd);
			if (!(cmd->cmd = tokenize(pipes[j++], " \t\n", cmd, 1)))
			{
				free(dup);
				free_t_cmd(cmd_general);
				return (1);
			}
			cmd->nb = size - j;
			if (cmd->in)
				free(cmd->in);
			if (cmd->out)
				free(cmd->out);
			cmd->in = NULL;
			cmd->out = NULL;
			cmd->nb_pipes = size;
			if (cmd->nb == size - 1 && cmd_general->in)
				cmd->in = ft_strdup(cmd_general->in);
			if (!cmd->nb && cmd_general->out)
				cmd->out = ft_strdup(cmd_general->out);
			ft_lstadd_back(cmds, ft_lstnew(cmd));
		}
		free(dup);
		free_array(pipes);
		free_t_cmd(cmd_general);
	}
	free_array(lines);
	return (0);
}
