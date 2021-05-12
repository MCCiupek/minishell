#include "minishell.h"

int         str_isdigit(char *str)
{
    int     i;

    i = 0;
    while (i < ft_strlen(str))
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void		builtin_exit(char **builtin, t_list *env, t_list *hist, int silence, int ret)
{
    int     i;
    //struct termios term;

    i = 0;
    if (builtin && array_len(builtin) > 2)
    {
        printf("minishell: exit: too many arguments\n");
        return;
    }
    if (builtin && array_len(builtin) > 1 && str_isdigit(builtin[1]))
    {
        ret = ft_atoi(builtin[1]);
    }
    if (!silence)
	    printf("exit\n");
    while (builtin && builtin[i])
    {
        free(builtin[i]);
        builtin[i] = NULL;
        i++;
    }
    if (env)
        ft_lstclear(&env, free);
	term_off();
    if (hist)
    	ft_lstclear(&hist, free);
    //tcgetattr(fileno(stdin), &term);
	//term.c_lflag |= ICANON | ECHO | ISIG;
    //tcsetattr(fileno(stdin), TCSANOW, &term);
	exit(ret);
}
