/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:52:13 by mciupek           #+#    #+#             */
/*   Updated: 2021/07/13 20:52:14 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_tokens(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		ft_putstr_fd(tokens[i++], STDOUT);
		if (tokens[i])
			ft_putchar_fd(' ', STDOUT);
	}
}

static int	print_env_var(char *s, char quote, t_list *env)
{
	char	**tokstr;
	char	*envstr;
	int		len_var;

	if (!s[1])
	{
		ft_putchar_fd('$', STDOUT);
		return (1);
	}
	envstr = str_env_var(s, &len_var, env);
	len_var = get_len(s);
	if (!envstr)
		return (len_var);
	if (quote == '\"')
	{
		ft_putstr_fd(envstr, STDOUT);
		return (len_var);
	}
	tokstr = tokenize(envstr, " \t\n", NULL, 0);
	print_tokens(tokstr);
	free(envstr);
	free_array(tokstr);
	return (len_var);
}

void	raise_flags(char *cmd, int *i, char *quote, char *bs)
{
	if (cmd[i] == '\\')
	{
		(*i)++;
		*bs = 1;
	}
	if (ft_strchr("\"\'", cmd[i]) && !quote && !bs)
		*quote = cmd[i++];
	if (quote && quote == cmd[i] && !bs)
	{
		(*i)++;
		*quote = 0;
	}
}

int	print_cmd(char *cmd, t_list *env)
{
	int		i;
	char	quote;
	char	bs;

	i = 0;
	bs = 0;
	quote = 0;
	while (cmd[i])
	{
		raise_flags(cmd, &i, &quote, &bs);
		if (cmd[i] == '$' && !bs && quote != '\'')
			i += print_env_var(&cmd[i], quote, env) + 1;
		else
			ft_putchar_fd(cmd[i++], STDOUT);
		bs = 0;
	}
	return (1);
}
