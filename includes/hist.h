#ifndef HIST_H
# define HIST_H

# include "minishell.h"

typedef struct  pos
{
    int         hist;
    int         line;
    int         curs;
}				t_pos;

char	*history_up(int hist_pos, t_list *hist);
char	*history_down(int hist_pos, t_list *hist);
t_list	*update_hist(char *line, t_list *hist);
char	*access_history(char c, t_pos *pos, t_list *hist);

#endif
