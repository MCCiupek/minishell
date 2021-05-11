#include "minishell.h"

void		builtin_exit(char **builtin, t_list *env, t_list *hist, int silence, int ret)
{
    int     i;

    i = 0;
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
    //printf("%d\n", ret);
	exit(ret);
}
