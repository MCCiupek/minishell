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

int	detect_quote_behavior(char quote, int was_print, char *s, t_list *env)
{
	int		nb_quotes;

	nb_quotes = ft_countchar(s, quote);
	if ((!quote || (quote == '\"' && ft_iseven(nb_quotes)) \
		|| (quote == '\'' && ft_iseven(nb_quotes))))
	{
		if (replace_and_print(s, env, 1, 0) == -2)
			was_print = 0;
	}
	else if (quote == '\"' && !ft_iseven(nb_quotes))
		replace_and_print(s, env, 0, 0);
	else if (quote == '\'' && !ft_iseven(nb_quotes))
		ft_putstr_fd_without_char(s, 1, quote);
	else
	{
		if (ft_strlen(s) == 0)
			was_print = 0;
		ft_putstr_fd(s, 1);
	}
	return (was_print);
}

char	get_quote_type(char **cmd, int i)
{
	char	quote;

	quote = 0;
	if (ft_strchr("\"\'", cmd[i][0]))
		quote = *ft_strchr("\"\'", cmd[i][0]);
	return (quote);
}

int	built_in_echo(char **cmd, t_list *env)
{
	int		new_line;
	int		was_print;
	int		i;

	i = 1;
	new_line = 1;
	(void)env;
	while (cmd[i] && is_n(cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		was_print = print_cmd(cmd[i], env);
		if (cmd[++i] && was_print == 1)
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
