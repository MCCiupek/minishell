/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 13:33:13 by fcivetta          #+#    #+#             */
/*   Updated: 2021/03/26 17:03:21 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_export(char **tab_env)
{
    int     i;
    int     j;
    int     equal;

    i = 0;
    while(tab_env[i])
    {
        j = 0;
        equal = 0;
        ft_putstr_fd("declare -x ", 1);
        while(tab_env[i][j])
        {
            ft_putchar_fd(tab_env[i][j], 1);
            if (tab_env[i][j] == '=' && equal == 0)
            {
                ft_putchar_fd('"', 1);
                equal = 1;
            }
            j++;
        }
        if (equal)
            ft_putchar_fd('"', 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
}

void    sort_env(t_list *env)
{
    char **tab_env;
    char *tmp;
    int     i;
    int     j;

    tab_env = lst_to_array(env);
    i = 0;
    while (tab_env[i])
    {
        j = i + 1;
        while (tab_env[j])
        {
            if(ft_strncmp(tab_env[i], tab_env[j], ft_strlen(tab_env[i])))
            {
                tmp = tab_env[i];
                tab_env[i] = tab_env[j];
                tab_env[j] = tmp;
            }
            j++;
        }
        i++;
    }
    print_export(tab_env);
    free_array(tab_env);
}

int     check_export_name(char *cmd)
{
    int     i;
    int     alpha_found;

    i = 0;
    alpha_found = 0;
    if (!cmd || !cmd[0] || cmd[0] == '=')
        return(0);
    while(cmd[i] && cmd[i] != '=')
    {
        if (ft_isalpha(cmd[i]))
            alpha_found = 1;
        else
        {
            if (ft_isdigit(cmd[i]) && !alpha_found)
                return(0);
            else if (!ft_isdigit(cmd[i]) && cmd[i] != '_')
                return(0);
        }
        i++;
    }
    return(1);
}

int    builtin_export(char **cmd, t_list *env)
{
    int     i;

    i = 1;
    if(!cmd[1]) 
    {
        sort_env(env);
        return(1);
    }
    while(cmd[i])
    {
    //   if(ft_strncmp(cmd[i]), env->var, ft_strlen(cmd[i]))
        if (!check_export_name(cmd[i]))
        {
            ft_putstr_fd("minishell: export: '", 2);
            ft_putstr_fd(cmd[i], 2);
            ft_putstr_fd("': not a valid identifier\n", 2);
        }
        //add(cmd[i], i);
        i++;
    }
    return(1);
}
