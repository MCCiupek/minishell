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
	int		background;
	char	*in;
	int		err;
}				t_cmd;

char			*msg_syn_err(char token);
char			check_line(char *line);
int				fill_redir(char **cmd, t_cmd *c, char *tok);
char			**tokenize(char *str, char *sep, t_cmd *c, int redir);
int				parse_cmd(char *line, t_list **cmds);

#endif
