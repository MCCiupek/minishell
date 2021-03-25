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

typedef struct  s_cmd
{
	int		nb_arg;
	int		max_arg;
	char	**cmd;
    char	*out;
    char	*in;
    char	*err;
}				t_cmd;

typedef struct  t_cmds
{
    int		n_cmd;
    int		max_cmd;
    t_list	*cmds;
    int		background;
}				t_cmds;

void		parse_cmd(char *line, t_cmds *cmds);

#endif
