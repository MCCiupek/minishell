/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo_replace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 18:30:01 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/12 18:30:03 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_skipping_spaces(int nb_quotes, int i, char *dup)
{
	char	*tok;
	int		last_space;
	int		is_first;

	is_first = 0;
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

int	free_dup_and_set_return_value(char *dup)
{
	if (ft_strlen(dup) == 0)
	{
		free(dup);
		return (-2);
	}
	free(dup);
	return (0);
}

void	replace_and_print_two_blocks(char *dup, int to_sep, t_list *env)
{
	if (*dup == '\"' || *dup == '\'')
	{
		replace_and_print(copy_begin(dup, to_sep), env, 0, 0);
		if ((dup[to_sep] == '\"' || dup[to_sep] == '\'') && \
			!ft_iseven(ft_countchar(dup + to_sep, \
			*ft_strchr("\"\'", dup[to_sep]))))
			replace_and_print(dup + to_sep, env, 0, 0);
		else
		{
			ft_putchar_fd(' ', 1);
			replace_and_print(dup + to_sep, env, 1, 0);
		}
	}
	else
	{
		print_len(dup, to_sep);
		if (!ft_iseven(ft_countchar(dup + to_sep, \
			*ft_strchr("\"\'", dup[to_sep]))))
			replace_and_print(dup + to_sep, env, 0, 0);
		else
		{
			ft_putchar_fd(' ', 1);
			replace_and_print(dup + to_sep, env, 1, 1);
		}
	}
}

int	replace_and_print(char *s, t_list *env, int skip_spaces, int i)
{
	char	*dup;
	int		to_sep;
	int		nb_quotes;

	i++;
	dup = ft_strdup(s);
	to_sep = is_outside_quote(dup);
	if (to_sep > 0)
	{
		replace_and_print_two_blocks(dup, to_sep, env);
		free(dup);
		return (0);
	}
	nb_quotes = ft_countchar(dup, '\"'); // ajouter les single si ca marche
	dup = replace_env_var(dup, "\"\'", env, 1, 0);
	if (*dup == '\"' && !ft_iseven(ft_countchar(dup, *ft_strchr("\"\'", *dup))))
		replace_and_print(dup, env, 0, 0);
	else if (skip_spaces)
		print_skipping_spaces(nb_quotes, i, dup);
	else
		ft_putstr_fd(dup, 1);
	return (free_dup_and_set_return_value(dup));
}
