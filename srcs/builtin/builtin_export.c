/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:58:30 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/05 16:58:33 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_check_input(char *input, int replace)
{
	int		i;
	int		alpha;
	int		eq;

	alpha = 0;
	i = 0;
	eq = 0;
	if (!input[i] || ft_strchr(" |=><:;\'\"", input[i]))
	{
		export_print_error(input, replace);
		return (0);
	}
	while (input[i])
	{
		if (ft_isalpha(input[i]))
			alpha = 1;
		else if (ft_isdigit(input[i]) && (alpha == 0))
			return (export_print_error(input, replace));
		else if (eq == 0 && ft_strchr(" |><:;\'\"", input[i]))
			return (export_print_error(input, replace));
		if (input[i] == '=' && eq == 0)
			eq = 1;
		i++;
	}
	return (1);
}

void	export_replace_env(char *newenv, t_list *env)
{
	char	*old;
	char	*tmp;
	char	*new;
	int		sp_i;

	sp_i = 0;
	new = ft_strrchr(newenv, '=') + 1;
	while (newenv[sp_i] && newenv[sp_i] != '=')
		sp_i++;
	old = malloc(sizeof(char) * ft_strlen(newenv) + 1);
	if (!old)
		return ;
	ft_strlcpy(old, newenv, sp_i + 1);
	tmp = ft_strrchr(get_env_var(old, env, 1), '=') + 1;
	free(old);
	ft_strlcpy(tmp, new, ft_strlen(new) + 1);
}

void	export_new_element(t_list *env, char *newenv)
{
	char	*tmp_str;

	tmp_str = ft_strjoin(newenv, "\0");
	ft_lstadd_back(&env, ft_lstnew(tmp_str));
}

void	export_update_env(char *newenv, t_list *env)
{
	t_list	*tmp;
	int		existing;
	int		len;

	tmp = env;
	existing = 0;
	len = 0;
	while (newenv[len] && newenv[len] != '=')
		len++;
	while (tmp)
	{
		if (newenv[len] == '=' && is_in_list(newenv, tmp, len))
		{
			check_space(tmp->content);
			export_replace_env(newenv, env);
			existing = 1;
		}
		else if (is_in_list(newenv, tmp, len))
			existing = 1;
		tmp = tmp->next;
	}
	if (!existing)
		export_new_element(env, newenv);
}

int	builtin_export(char **cmd, t_list *env)
{
	size_t		i;
	char		*dup;

	i = 1;
	if (ft_arraysize(cmd) == 1)
		export_sort_env(env);
	while (cmd[i])
	{
		if (export_check_input(cmd[i], 1))
		{
			dup = ft_strdup(cmd[i]);
			dup = replace_env_var(dup, "\"\'", 1, 1);
			if (!dup[0] && ft_strchr(cmd[i], '$'))
				export_sort_env(env);
			else if (export_check_input(dup, 0))
				export_update_env(dup, env);
			free(dup);
		}
		i++;
	}
	return (1);
}
