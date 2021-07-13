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

int	print_env_var(char *s, t_list *env, char quote)
{
	char	**tokstr;
	char	*envstr;
	int		len_var;
	int		i;

	if (!s[1])
	{
		ft_putchar_fd('$', STDOUT);
		return (1);
	}
	envstr = replace(s, 0, env, &len_var);
	if (!envstr)
		return (len_var);
	if (quote == '\"')
	{
		ft_putstr_fd(envstr, STDOUT);
		return (len_var);
	}
	else
		tokstr = tokenize(envstr, " \t\n", NULL, 0);
	i = 0;
	while (tokstr[i])
	{
		ft_putstr_fd(tokstr[i++], STDOUT);
		if (tokstr[i])
			ft_putchar_fd(' ', STDOUT);
	}
	free_array(tokstr);
	return (len_var);
}

void	print_cmd(char *cmd, t_list *env)
{
	int		i;
	char	quote;
	char	bs;

	i = 0;
	bs = 0;
	quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\\')
		{
			i++;
			bs = 1;
		}
		if (ft_strchr("\"\'", cmd[i]) && !quote && !bs)
		{
			quote = cmd[i++];
			continue ;
		}
		if (quote && quote == cmd[i] && !bs)
		{
			i++;
			quote = 0;
			continue ;
		}
		if (cmd[i] == '$' && !bs)
			i += print_env_var(&cmd[i], env, quote);
		else
			ft_putchar_fd(cmd[i++], STDOUT);
		bs = 0;
	}
}

int	built_in_echo(char **cmd, t_list *env)
{
	int		new_line;
	int		was_print;
	int		i;
	//char	quote;

	i = 1;
	new_line = 1;
	while (cmd[i] && is_n(cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		//printf("cmd[%d]: %s\n", i, cmd[i]);
		print_cmd(cmd[i], env);
		was_print = 1;
		//quote = get_quote_type(cmd, i);
		//was_print = detect_quote_behavior(quote, was_print, cmd[i], env);
		if (cmd[++i] && was_print == 1)
			ft_putchar_fd(' ', 1);
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
