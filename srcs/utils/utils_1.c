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

char    **lst_to_array(t_env   *env)
{
    t_env   *tmp;
    char    **tab;
    int     i;
    int		len;

    i = 0;
    tmp = env;
    len = 0;
//    while (tmp->next != NULL)
    while(tmp != NULL)
    {
	    len++;
	    tmp = tmp->next;
    }
    if(!(tab = (char **)malloc(sizeof(char *) * (len + 1))))
        error(MEM_ERR);
    tmp = env;
    while (tmp != NULL)
    {
        tab[i] = tmp->var;
        i++;
        tmp = tmp->next;
    }
    return (tab);
}
