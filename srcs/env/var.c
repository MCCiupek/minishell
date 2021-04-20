/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:24:19 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/12 14:24:24 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char     *ft_skipchar(char *s, int i)
{
    char *copy;

    if (s)
    {
        copy = (char *)malloc(sizeof(s) * (strlen(s) + 1));
        ft_strlcpy(copy, s, i + 1);
        copy = ft_strjoin(copy, &s[i + 1]);
        return (copy);
    }
    return (NULL);
}

static char *ft_strnchr(char *s, char *chars)
{
    int i;

    i = 0;
    while (!ft_strchr(chars, s[i]))
        i++;
    return (&s[i]);
}

static int ft_locnchr(char *s, char *chars)
{
    int i;

    i = 0;
    while (!ft_strchr(chars, s[i]))
        i++;
    return (i);
}

static char	*replace(char *s, int i, t_list *env, int err)
{
	t_list	*tmp;
    char    *copy;

	tmp = env;
    if (s)
    {
        copy = (char *)malloc(sizeof(s) * (i + 1));
        ft_strlcpy(copy, s, i + 1);
        if (ft_strncmp("?", &s[i] + 1, ft_locnchr(&s[i], " \\") - 1) == 0)
        {
            copy = ft_strjoin(copy, ft_itoa(err));
            copy = ft_strjoin(copy, ft_strnchr(&s[i], " \\"));
            return (copy);
        }
        while (tmp)
        {
            if (ft_strncmp((char *)tmp->content, &s[i] + 1, ft_locnchr(&s[i], " \\") - 1) == 0)
            {
                copy = ft_strjoin(copy, ft_strchr((char *)tmp->content, '=') + 1);
                copy = ft_strjoin(copy, ft_strnchr(&s[i], " \\"));
                return (copy);
            }
            tmp = tmp->next;
        }
        copy = ft_strjoin(copy, ft_strnchr(&s[i], " \\"));
        return (copy);
    }
	return (s);
}

char     *replace_env_var(char *cmd, char *quotes, t_list *env, int err)
{
    int     i;
    char    c;

    i = -1;
    c = 0;
    while (cmd && cmd[++i])
    {
        if (c && cmd[i] == c)
        {
            c = 0;
            cmd = ft_skipchar(cmd, i);
        }
        if (!c && ft_strchr(quotes, cmd[i]))
        {
            c = cmd[i];
            cmd = ft_skipchar(cmd, i);
        }
        if (cmd[i] == '$' && c != '\'' && cmd[i + 1])
            cmd = replace(ft_strtrim(cmd, &c), i, env, err);
    }
    return (cmd);
}

int     replace_in_cmd(t_cmd *cmd, char *quotes, t_list *env)
{
    int i;

    i = -1;
    while (cmd->cmd[++i])
        cmd->cmd[i] = replace_env_var(cmd->cmd[i], quotes, env, cmd->err);
	cmd->in = replace_env_var(cmd->in, quotes, env, cmd->err);
    cmd->out = replace_env_var(cmd->out, quotes, env, cmd->err);
    return (0);
}