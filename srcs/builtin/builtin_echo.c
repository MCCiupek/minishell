/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:22:04 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/13 16:22:05 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_envvar(char *s, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, s + 1, ft_strlen(s) - 1) == 0)
		{
			ft_putstr_fd((char *)tmp->content + (ft_strlen(s)), 1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	echo_env(char *s, t_list *env)
{
	print_envvar(s, env);
}

static int	is_n(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (0);
	while (s[i])
		if (s[i++] != 'n')
			return (0);
	return (1);
}

int	replace_and_print(char *s, t_list *env, int skip_spaces)
{
	char	*dup;
	char	*tok;
	int		is_first;

	dup = ft_strdup(s);
	dup = replace_env_var(dup, "\"\'", env, 0, 1);
	is_first = 0;
	if (*dup == '\"' && !ft_iseven(ft_countchar(dup, *ft_strchr("\"\'", *dup)))) //
		replace_and_print(dup, env, 0); //
	else if (skip_spaces)
	{
		tok = ft_strmbtok(dup, " \t\n", NULL, 0);
		while (tok)
		{
			if (tok && ft_strlen(tok) > 0)
			{	
				ft_putstr_fd(tok, 1);
				is_first++;
			}
			tok = ft_strmbtok(NULL, " \t\n", NULL, 0);
			if (is_first && tok && ft_strlen(tok) > 0)
				ft_putchar_fd(' ', 1);
		}
	}
	else
		ft_putstr_fd(dup, 1);
	free(dup);
	return (0);
}

int	built_in_echo(char **cmd, t_list *env)
{
	int		new_line;
	int		i;
	int		nb_quotes;
	char	quote;

	i = 1;
	new_line = 1;
	while (cmd[1] && is_n(cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		quote = 0;
		if (ft_strchr("\"\'", cmd[i][0]))
			quote = *ft_strchr("\"\'", cmd[i][0]);
		nb_quotes = ft_countchar(cmd[i], quote);
		if (!quote || (quote == '\"' && ft_iseven(nb_quotes)) || (quote == '\'' && ft_iseven(nb_quotes)))
			replace_and_print(cmd[i], env, 1);
		else if (quote == '\"' && !ft_iseven(nb_quotes))
			replace_and_print(cmd[i], env, 0);
		else if (quote == '\'' && !ft_iseven(nb_quotes))
			ft_putstr_fd_without_char(cmd[i], 1, quote);
		else
			ft_putstr_fd(cmd[i], 1);
		if (cmd[++i])
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
