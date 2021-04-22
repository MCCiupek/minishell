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

void        delete_backspace(int i)
{
    char    *dc;
    char    *le;
    char    *buf;

    if (i > 0)
    {
        buf = malloc(2048);
        int ret;
        ret = tgetent(buf, getenv("TERM"));
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