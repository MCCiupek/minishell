#include "minishell.h"

void		builtin_exit(char **builtin, t_list *env)
{
    int     i;

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
	exit(EXIT_SUCCESS);
}
