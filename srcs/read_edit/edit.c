#include "minishell.h"
# include <curses.h>
# include <term.h>

int	ft_putchar(int n)
{
    char c;

    c = (char)n;
	write(1, &c, 1);
    return (1);
}

void        delete_to_replace(int i)
{
    char    *buf;
    int     ret;

    buf = malloc(2048);
    while (i > 0)
    {
        i--;
        ret = tgetent(buf, getenv("TERM"));
        tputs(tgetstr("le", NULL), 1, ft_putchar);
        tputs(tgetstr("dc", NULL), 1, ft_putchar);
    }
    free(buf);
}

static char **split_cursor_val(const char *s)
{
    int     k;
    char    **new;

    k = 0;
    while (*(s + k) && (*(s + k) == 27 || *(s + k) == '['))
        k++;
    new = ft_split((s + k), ';');
    return (new);
}

void        get_current_cursor(int *i, int *j)
{
    char    buf[16];
    char    **sp_buf;

    ft_bzero(&buf, 16);
    write(1, "\033[6n", ft_strlen("\033[6n"));
    read(1, &buf, 16);
    sp_buf = split_cursor_val(buf);
    *i = ft_atoi(sp_buf[0]) - 1;
    *j = ft_atoi(sp_buf[1]) - 1;
    free(sp_buf);
}

void        cursorleft(int *pos)
{
    int     i;
    int     j;
    char    *buf;

    if (*pos > 0)
    {
        *pos = *pos - 1;
        buf = malloc(2048);
        get_current_cursor(&i, &j);
        tgetent(buf, getenv("TERM"));
        tputs(tgoto(tgetstr("cm", NULL), j - 1, i), 1, ft_putchar);
        free(buf);
    }
}

void        cursorright(int *pos, int max_pos)
{
    if (*pos < max_pos)
    {
        *pos = *pos + 1;
        tputs(tgetstr("nd", NULL), 1, ft_putchar);
    }
}

char    *update_line_end(char *line)
{
    int len;

    len = ft_strlen(line);
    line[len - 1] = '\0';
    return (line);
}

char    *update_line_mid(char *line, t_pos *pos)
{
    char	*end;
	char	*begin;

    begin = cp_begin_str(pos, line);
    end = ft_strdup(line + pos->curs + 1);
    free(line);
    line = ft_strjoin(begin, end);
    free(begin);
    free(end);
    return (line);
}

char        *delete_backspace(t_pos *pos, char *line)
{
    char    *buf;

	if (pos->curs > 0)
    {
		if (pos->line > 0)
		{
			buf = malloc(2048);
			int ret;
			ret = tgetent(buf, getenv("TERM"));
			tputs(tgetstr("le", NULL), 1, ft_putchar);
			tputs(tgetstr("dc", NULL), 1, ft_putchar);
            free (buf);
		}
        if (pos->curs == pos->line)
        {
            line = update_line_end(line);
            pos->curs--;
        }
        else if (pos->curs < pos->line)
        {
            pos->curs--;
            line = update_line_mid(line, pos);
        }
        pos->line--;
    }
	return (line);
}

void		insert_char(char c)
{
    char    *buf;

    buf = malloc(2048);
    tgetent(buf, getenv("TERM"));
    tputs(tgetstr("sc", NULL), 1, ft_putchar);
    tputs(tgetstr("im", NULL), 1, ft_putchar);
    tputs(tgetstr("ic", NULL), 1, ft_putchar);
    ft_putchar((int)c);
    tputs(tgetstr("ei", NULL), 1, ft_putchar);
    tputs(tgetstr("rc", NULL), 1, ft_putchar);
    tputs(tgetstr("nd", NULL), 1, ft_putchar);
    free(buf);
}
