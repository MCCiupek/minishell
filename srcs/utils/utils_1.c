/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:16:29 by fcivetta          #+#    #+#             */
/*   Updated: 2021/03/26 16:32:41 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **lst_to_array(t_list   *env)
{
    t_list   *tmp;
    char    **tab;
    int     i;
    int		len;

    i = 0;
    len = ft_lstsize(env);
    if(!(tab = (char **)malloc(sizeof(char *) * (len + 1))))
        error(MEM_ERR);
    tmp = env;
    while (tmp)
    {
        tab[i++] = tmp->content;
        tmp = tmp->next;
    }
    return (tab);
}

void    free_t_cmd(void *ptr)
{
    int     i;
    t_cmd   *cmd;

    i = 0;
    cmd = (t_cmd *)ptr;
    while (cmd->cmd[i])
        free(cmd->cmd[i++]);
    if (cmd->in)
        free(cmd->in);
    if (cmd->out)
        free(cmd->out);
    //return (NULL);
}
