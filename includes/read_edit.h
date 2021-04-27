#ifndef READ_EDIT_H
# define READ_EDIT_H

# include "minishell.h"

char		*read_line(t_list *env, t_cmds *cmds, t_list *hist);
char        *delete_backspace(t_pos *pos, t_list *env, char *line);
int	        ft_putchar(int n);
char        *update_line(char *line);
void        delete_to_replace(int i);
int        cursorleft(int *pos, t_list *env);
void        cursorright(int *pos, t_list *env, int max_pos);
char		*cp_begin_str(t_pos *pos, char *line);

#endif
