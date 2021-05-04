#ifndef READ_EDIT_H
# define READ_EDIT_H

# include "minishell.h"

char		*read_line(t_list *hist, t_list *env);
char        *delete_backspace(t_pos *pos, char *line);
int	        ft_putchar(int n);
char        *update_line(char *line);
void        delete_to_replace(int i);
void        cursorleft(int *pos);
void        cursorright(int *pos, int max_pos);
char		*cp_begin_str(t_pos *pos, char *line);
void		insert_char(char c);

#endif
