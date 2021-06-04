/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:06:39 by mciupek           #+#    #+#             */
/*   Updated: 2021/05/12 16:06:41 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIST_H
# define HIST_H

# include "minishell.h"

typedef struct s_pos
{
	int	hist;
	int	line;
	int	curs;
}				t_pos;

char			*history_up(int hist_pos, t_list *hist);
char			*history_down(int hist_pos, t_list *hist);
t_list			*update_hist(char *line, t_list *hist);
char			*access_history(char c, t_pos *pos, t_list *hist);

#endif
