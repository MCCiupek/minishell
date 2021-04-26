#ifndef READ_EDIT_H
# define READ_EDIT_H

# include "minishell.h"

char		*read_line(t_list *env, t_cmds *cmds, t_list *hist);
//static char	*fill_line(char *line, t_cmds *cmds, t_list *hist, t_list *env);
void        delete_backspace(int i, t_list *env);
int	        ft_putchar(int n);
char        *update_line(char *line);
void        delete_to_replace(int i);
void        cursorleft(int *pos, t_list *env);
void        cursorright(int *pos, t_list *env, int max_pos);

#endif
