#include "minishell.h"

void		builtin_exit(char **builtin, t_list *env, t_list *hist)
{
    int     i;
    //struct termios term;

    i = 0;
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
	ft_lstclear(&hist, free);
    //tcgetattr(fileno(stdin), &term);
	//term.c_lflag |= ICANON | ECHO | ISIG;
    //tcsetattr(fileno(stdin), TCSANOW, &term);
	exit(EXIT_SUCCESS);
}
