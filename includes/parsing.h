/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:37:46 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/23 13:37:48 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd
{
	size_t	nb;
	size_t	nb_pipes;
	char	**cmd;
	char	*out;
	int		out_flags;
	char	*in;
	int		fdin;
	int		fdout;
	int		fd[2];
	int		err;
	int		is_env;
}				t_cmd;

char			*open_fd(int mode, char *redir, int *flags);
char			*msg_syn_err(char token);
void			ft_init_cmd(t_cmd *cmd);
int				ft_isempty(char *c, char *next, char s, char *sep);
char			ft_isquote(char c, int quote);
void			init(int *i, int *empty, int *quote);
char			check_line(char *line);
int				fill_redir(char **cmd, t_cmd *c, char *tok);
char			**tokenize(char *str, char *sep, t_cmd *c, int redir);
int				parse_cmd(char *line, t_list **cmds);

#endif
