/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:48:09 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/19 13:48:11 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>

# include "../libft/libft.h"

typedef struct  s_cmd
{
	int		nb_arg;
	int		max_arg;
	char	**cmd;
}				t_cmd;

typedef struct  t_cmds
{
    int		n_cmd;
    int		max_cmd;
    t_list	cmds;
    char	*out;
    char	*in;
    char	*err;
    int		background;
}				t_cmds;

#endif