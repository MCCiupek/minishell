#include "minishell.h"

void		builtin_exit(char **builtin, t_list *env)
{
    int     i;

    i = 0;
	printf("%s", "exit\n");
   while (builtin[i])
    {
        free(builtin[i]);
        builtin[i] = NULL;
        i++;
    }
    if (env)
        printf("env à free\n");
	exit(EXIT_SUCCESS);
}
