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
    char    *dc;
    char    *le;
    char    *buf;
    int     ret;

    buf = malloc(2048);
    while (i > 0)
    {
        i--;
        ret = tgetent(buf, getenv("TERM")); // utiliser get_env_var
        le = tgetstr("le", NULL);
        dc = tgetstr("dc", NULL);
        tputs(le, 1, ft_putchar);
        tputs(dc, 1, ft_putchar);
    }

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

int        get_current_cursor(int *i, long int *j)
{
    char    buf[16];
    char    **sp_buf;
    int     ret;

    ft_bzero(&buf, 16);
    write(1, "\033[6n", ft_strlen("\033[6n"));
    ret = read(1, &buf, 16);
   // printf("\n--------\nbuf='%i', read=%i\n", (int)buf, ret);
   if (ret == 1)
        return (-1);
    sp_buf = split_cursor_val(buf);
 //   printf("i=%i, j=%li\n", *i, *j);
    *i = ft_atoi(sp_buf[0]) - 1;
 //   printf("%s\n", sp_buf[1]);
    *j = ft_atoi(sp_buf[1]) - 1;
 //   printf("4\n");
    free(sp_buf);
    return (0);
}

int        cursorleft(int *pos, t_list *env)
{
    char    *buf;
    int     i;
    long int     j;
    char    *cm;
    char    *gt;
    int     ret;

    ret = 0;

    if (*pos > 0)
    {
        *pos = *pos - 1;
        buf = malloc(2048);
        ret = get_current_cursor(&i, &j);
        if (ret == -1)
            return (-1);
        tgetent(buf, ft_strrchr(get_env_var("TERM=", env), '=') + 1);
        cm = tgetstr("cm", NULL);
        gt = tgoto(cm, j - 1, i);
        tputs(gt, 1, ft_putchar);
    }
    return (0);
}

void        cursorright(int *pos, t_list *env, int max_pos)
{
    char    *buf;
    int     i;
    long int     j;
    char    *cm;
    char    *gt;

    if (*pos < max_pos)
    {
        *pos = *pos + 1;
        buf = malloc(2048);
        get_current_cursor(&i, &j);
        tgetent(buf, ft_strrchr(get_env_var("TERM=", env), '=') + 1);
        cm = tgetstr("cm", NULL);
        gt = tgoto(cm, j + 1, i);
        tputs(gt, 1, ft_putchar);
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

char        *delete_backspace(t_pos *pos, t_list *env, char *line)
{
	char    *dc;
    char    *le;
    char    *buf;

	if (pos->curs > 0)
    {
		if (pos->line > 0)
		{
			buf = malloc(2048);
			int ret;
			ret = tgetent(buf, ft_strrchr(get_env_var("TERM=", env), '=') + 1);
			le = tgetstr("le", NULL);
			dc = tgetstr("dc", NULL);
			tputs(le, 1, ft_putchar);
			tputs(dc, 1, ft_putchar);
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
