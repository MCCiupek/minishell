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

    buf = malloc(2048);
    while (i > 0)
    {
        i--;
        int ret;
        ret = tgetent(buf, getenv("TERM"));
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

void        cursorleft(int *pos, t_list *env)
{
    char    *buf;
    int     i;
    int     j;
    char    *cm;
    char    *gt;

    if (*pos > 0)
    {
        *pos = *pos - 1;
        buf = malloc(2048);
        get_current_cursor(&i, &j);
        tgetent(buf, ft_strrchr(get_env_var("TERM=", env), '=') + 1);
        cm = tgetstr("cm", NULL);
        gt = tgoto(cm, j - 1, i);
        tputs(gt, 1, ft_putchar);
    }
}

void        cursorright(int *pos, t_list *env, int max_pos)
{
    char    *buf;
    int     i;
    int     j;
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

void        delete_backspace(int i, t_list *env)
{
    char    *dc;
    char    *le;
    char    *buf;

    if (i > 0)
    {
        buf = malloc(2048);
        int ret;
        ret = tgetent(buf, ft_strrchr(get_env_var("TERM=", env), '=') + 1);
        le = tgetstr("le", NULL);
        dc = tgetstr("dc", NULL);
        tputs(le, 1, ft_putchar);
        tputs(dc, 1, ft_putchar);
    }
}

char    *update_line(char *line)
{
    int len;

    len = ft_strlen(line);
    line[len - 1] = '\0';
    return (line);
}