#include "minishell.h"

void		init_pos(t_pos *pos)
{
	pos->line = 0;
	pos->hist = 0;
    pos->curs = 0;
}

void		display_char_end(char c, t_pos *pos, char *line)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	line[pos->line] = c;
	pos->line++;
	pos->curs++;
	line[pos->line] = '\0';
}

char		*cp_begin_str(t_pos *pos, char *line)
{
	int		i;
	char	*begin;
//	char	begin[pos->curs];

	i = 0;
	begin = NULL;
	begin = (char *)malloc(sizeof(char *) * (pos->curs + 1));
	if (!begin)
		return (NULL);
	ft_strlcpy(begin, line, pos->curs + 1);
	begin[pos->curs] = '\0';
	return (begin);
}

char		*display_char_mid(char c, t_pos *pos, char *line, t_list *env)
{
	char	*end;
	char	*begin;
	char	mid[2];
	int		to_store;
	int		i;

	mid[0] = c;
	mid[1] = '\0';
	to_store = pos->line - pos->curs;
	end = ft_strdup(line + pos->curs);
	begin = cp_begin_str(pos, line);
//	printf("\nnewstr=%s|%s|%s\n", begin, mid, end);
	ft_putchar_fd(c, STDOUT_FILENO);
	i = 0;
	while (end[i])
	{
		ft_putchar_fd(end[i], STDOUT_FILENO);
		i++;
	}
/*	if (!env)
		printf("zaeg"); */
	int j;
	int ret;
	j = pos->line + 1;
	line = ft_strjoin(begin, mid);
	line = ft_strjoin(line, end);
	pos->line = ft_strlen(line);
	pos->curs++;
	ret = 0;
	while (j > pos->curs && ret >= 0)
		ret = cursorleft(&j, env);
	free(begin);
	free(end);
	return (line);
}

static char	*fill_line(char *line, t_cmds *cmds, t_list *hist, t_list *env)
{
	char	buf[6];
	t_pos	pos;
	int r;

	buf[0] = '\0';
	if (!cmds)
		printf("blabala\n"); //à remove qd on se servira de cmds
	init_pos(&pos);
	while (buf[0] != '\n')
	{
		r = read(STDIN_FILENO, buf, 5);
		buf[r] = '\0';
		if (buf[0] == 127)
			line = delete_backspace(&pos, env, line);
		else if (!ft_strncmp(buf, "\033[A", 4))
			line = access_history('u', &pos, hist, line);
		else if (!ft_strncmp(buf, "\033[B", 4))
			line = access_history('d', &pos, hist, line);
		else if (!ft_strncmp(buf, "\033[C", 4))
			cursorright(&pos.curs, env, pos.line);
		else if (!ft_strncmp(buf, "\033[D", 4))
			cursorleft(&pos.curs, env);
		else if (!ft_strncmp(buf, "\003", 4))
			printf("ctrl c?\n");
		else if (!ft_strncmp(buf, "\004", 4))
			printf("ctrl d?\n");
		else if (r > 0)
		{
			if (r == 1 && buf[0] != '\n' && buf[0] != '\034')
			{
				if (pos.curs == pos.line)
					display_char_end(buf[0], &pos, line);
				else if (pos.curs < pos.line)
					line = display_char_mid(buf[0], &pos, line, env);
			}
		}
	//	printf("\nLINE STATUS:\npos: curs=%i|line%i\nline=%s\n", pos.curs, pos.line, line);
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
	line = fill_line(line, cmds, hist, env);
	write(STDOUT_FILENO, "\n", 1);
	return (line);
}