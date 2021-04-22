#include "minishell.h"

static char	*fill_line(char *line, t_cmds *cmds, t_list *hist)
{
	char	buf[6];
	buf[0] = '\0';

	int hist_pos;
	int r;
	int line_pos;
    int curs_pos;
	if (!cmds)
		printf("blabala\n"); //à remove qd on se servira de cmds
	line_pos = 0;
	hist_pos = 0;
    curs_pos = 0;
	while (buf[0] != '\n')
	{
		r = read(STDIN_FILENO, buf, 5);
		buf[r] = '\0';
		if (buf[0] == 127)
        {
            if (line_pos > 0)
            {
                delete_backspace(line_pos);
                line_pos--;
                line = update_line(line);
            }
        }
		else if (!ft_strncmp(buf, "\033[A", 4))
		{
            if (hist_pos < ft_lstsize(hist))
				hist_pos++;
            if (hist_pos > 0)
            {
                delete_to_replace(line_pos);
	    		line = ft_strdup(history_up(hist_pos, hist));
            }
            line_pos = ft_strlen(line);
		}
		else if (!ft_strncmp(buf, "\033[B", 4))
		{
            if (hist_pos > 0) 
				hist_pos--;
            if (hist_pos >= 0)
            {
                delete_to_replace(line_pos);
			    line = ft_strdup(history_down(hist_pos, hist));
            }
            line_pos = ft_strlen(line);
		}
		else if (!ft_strncmp(buf, "\033[C", 4))
			printf("go right\n");
		else if (!ft_strncmp(buf, "\033[D", 4))
			printf("go left\n");
		else if (!ft_strncmp(buf, "\003", 4))
			printf("ctrl c?\n");
		else if (!ft_strncmp(buf, "\004", 4))
			printf("ctrl d?\n");
		else if (r > 0)
		{
			if (r == 1 && buf[0] != '\n' && buf[0] != '\034')
			{
				ft_putchar_fd(buf[0], STDOUT_FILENO);
				line[line_pos] = buf[0];
				line_pos++;
				line[line_pos] = '\0';
			}
		}
	}
	return (line);
}

char		*read_line(t_list *env, t_cmds *cmds, t_list *hist)
{
	char	*line;
	char	*tmp;

	line = malloc(sizeof(char) * BUFFER_SIZE);
	if (!line)
		printf("ERROR\n"); //à modif
	line[0] = '\0';
	tmp = line;
	line = fill_line(line, cmds, hist);
	write(STDOUT_FILENO, "\n", 1);	
	if (!env)
		printf("fzjeo");
	return (line);
}