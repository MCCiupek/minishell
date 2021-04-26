#include "minishell.h"

void		builtin_exit(char **builtin, t_list *env)
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
        printf("env à free\n");
	term_off();
    //tcgetattr(fileno(stdin), &term);
	//term.c_lflag |= ICANON | ECHO | ISIG;
    //tcsetattr(fileno(stdin), TCSANOW, &term);
	exit(EXIT_SUCCESS);
}
