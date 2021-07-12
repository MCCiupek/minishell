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

int	is_outside_quote(char *s)
{
	int	k;
	int	quote_pos_open;
	int	quote_pos_close;
	int	in_quote;
	int	out_quote;
	int	is_env;
	int	nb_open;
	int	nb_close;

	k = 0;
	in_quote = 0;
	nb_open = 0;
	nb_close = 0;
	out_quote = 0;
	quote_pos_open = -1;
	is_env = 0;
	quote_pos_close = -1;
	while (s[k])
	{
		if (s[k] == '$' && quote_pos_close > -1)
			return (quote_pos_close + 1);
		else if (s[k] == '$' && quote_pos_open > -1)
			is_env = 1;
		else if ((s[k] == '\'' || s[k] == '\"') && in_quote == 0)
		{
			if (quote_pos_open == -1)
				quote_pos_open = k;
			nb_open++;
		}
		else if ((s[k] == '\'' || s[k] == '\"') && in_quote == 1)
		{
			if (k == 0 || s[k - 1] != '\\')
			{
				quote_pos_close = k;
				nb_close++;
				if (nb_close > nb_open)
					return (k);
			}
		}
		else if (quote_pos_open == -1 || quote_pos_close > -1)
			out_quote = 1;
		else 
			in_quote = 1;
		k++;
	}
//	printf("quote_pos_open=%i, quote_pos_close=%i, in_quote=%i, out_quote=%i, is_env=%i, nb_open=%i, nb_close=%i\n", quote_pos_open, quote_pos_close, in_quote, out_quote, is_env, nb_open, nb_close);
	if (out_quote == 1 && in_quote == 1 && is_env == 1)
		return (quote_pos_open);
	return (-1);
}

void	print_len(char *s, int k)
{
	int	i;

	i = 0;
	while (s[i] && i < k)
	{
		ft_putchar_fd(s[i], 1);
		i++;
	}
}

char	*copy_begin(char *s, int k)
{
	char *ret;

	ret = malloc(sizeof(char) * k + 1);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, s, k);
	ret[k] = '\0';
	return (ret);
}

int	replace_and_print(char *s, t_list *env, int skip_spaces, int i)
{
	char	*dup;
	char	*tok;
	int		is_first;
	int		to_sep;
	int		nb_quotes;
	int		last_space;

	i++;
	dup = ft_strdup(s);
	to_sep = is_outside_quote(dup);
	if (to_sep > 0)
	{
		if (*dup == '\"' || *dup == '\'')
		{
			replace_and_print(copy_begin(dup, to_sep), env, 0, 0);
			if ((dup[to_sep] == '\"' || dup[to_sep] == '\'') && !ft_iseven(ft_countchar(dup + to_sep, *ft_strchr("\"\'", dup[to_sep]))))
				replace_and_print(dup + to_sep, env, 0, 0);
			else
			{
				ft_putchar_fd(' ', 1);
				replace_and_print(dup + to_sep, env, 1, 0);
			}
			return (0);
		}
		else
		{
			print_len(dup, to_sep);
			if (!ft_iseven(ft_countchar(dup + to_sep, *ft_strchr("\"\'", dup[to_sep]))))
				replace_and_print(dup + to_sep, env, 0, 0);
			else
			{
				ft_putchar_fd(' ', 1);
				replace_and_print(dup + to_sep, env, 1, 1);
			}
			return (0);
		}
	}
	nb_quotes = ft_countchar(dup, '\"'); // ajouter les single si ca marche
//	printf("dup=[%s]\n", dup);
	dup = replace_env_var(dup, "\"\'", env, 1, 0);
//	printf("dup=[%s]\n", dup);
	is_first = 0;
	if (*dup == '\"' && !ft_iseven(ft_countchar(dup, *ft_strchr("\"\'", *dup))))
 	{
		replace_and_print(dup, env, 0, 0);
	}
	else if (skip_spaces)
	{
		if (nb_quotes > 0 && *dup == ' ' && i == 1)
			ft_putchar_fd(' ', 1);
		last_space = 0;
		if (nb_quotes > 0 && dup[ft_strlen(dup) - 1] == ' ')
			last_space = 1;
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
		if (last_space == 1)
			ft_putchar_fd(' ', 1);
	}
	else
		ft_putstr_fd(dup, 1);
	if (ft_strlen(dup) == 0)
	{
		free(dup);
		return (-2);
	}
	free(dup);
	return (0);
}

int	built_in_echo(char **cmd, t_list *env)
{
	int		new_line;
	int		was_print;
	int		i;
	int		nb_quotes;
	char	quote;

	i = 1;
	new_line = 1;
	while (cmd[i] && is_n(cmd[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		was_print = 1;
		quote = 0;
		if (ft_strchr("\"\'", cmd[i][0]))
			quote = *ft_strchr("\"\'", cmd[i][0]);
		nb_quotes = ft_countchar(cmd[i], quote);
		if ((!quote || (quote == '\"' && ft_iseven(nb_quotes)) || (quote == '\'' && ft_iseven(nb_quotes))))
		{
			if (replace_and_print(cmd[i], env, 1, 0) == -2)
				was_print = 0;
		}
		else if (quote == '\"' && !ft_iseven(nb_quotes))
		{
			replace_and_print(cmd[i], env, 0, 0);
		}
		else if (quote == '\'' && !ft_iseven(nb_quotes))
			ft_putstr_fd_without_char(cmd[i], 1, quote);
		else
		{
			if (ft_strlen(cmd[i]) == 0)
				was_print = 0;
			ft_putstr_fd(cmd[i], 1);
		}
		if (cmd[++i] && was_print == 1)
		{
			ft_putchar_fd(' ', 1);
		}
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
