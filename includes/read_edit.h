#ifndef READ_EDIT_H
# define READ_EDIT_H

# include "minishell.h"

char		*read_line(t_list *env, t_cmds *cmds, t_list *hist);
//static char	*fill_line(char *line, t_cmds *cmds, t_list *hist);
void        delete_backspace();
int	ft_putchar(int n);
char    *update_line(char *line);
void    delete_to_replace(int i);

#endif
