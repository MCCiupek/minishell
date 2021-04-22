#ifndef HIST_H
# define HIST_H

# include "minishell.h"

char	*history_up(int hist_pos, t_list *hist);
char	*history_down(int hist_pos, t_list *hist);
t_list	*update_hist(char *line, t_list *hist);
//void    delete_to_replace(int i);

#endif
