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

int			export_check_input(char *input)
{
	int		i;
	int		alpha;

	alpha = 0;
	i = 0;
	while (input[i])
	{
		if (ft_isalpha(input[i]))
			alpha = 1;
		else if (ft_isdigit(input[i]))
		{
			if (alpha == 0)
			{
				export_print_error(input);
				return (0);
			}
		}
		else if (input[i] != '=' && input[i] != '_')
		{
			export_print_error(input);
			return (0);
		}
		i++;
	}
	return (1);
}

void		export_replace_env(char *newenv, t_list *env)
{
	char	*old;
	char	*new;
	int		sp_i;

	sp_i = 0;
	new = ft_strrchr(newenv, '=') + 1;
	while (newenv[sp_i] && newenv[sp_i] != '=')
		sp_i++;
	old = malloc(sizeof(char) * sp_i + 1);
	ft_strlcpy(old, newenv, sp_i);
	old = ft_strrchr(get_env_var(old, env), '=') + 1;
	ft_strlcpy(old, new, ft_strlen(new) + 1);
}

void		export_update_env(char *newenv, t_list *env)
{
	t_list	*tmp;
	int		existing;
	int		len;
	char	*tmp_str;

	tmp = env;
	existing = 0;
	len = 0;
	while (newenv[len] && newenv[len] != '=')
		len++;
	while (tmp)
	{
		if (newenv[len] == '=' && (!(ft_strncmp(newenv, tmp->content, len))))
		{
			export_replace_env(newenv, env);
			existing = 1;
		}
		tmp = tmp->next;
	}
	if (!existing)
	{
		tmp_str = ft_strjoin(newenv, "\0");
		ft_lstadd_back(&env, ft_lstnew(tmp_str));
	}
}

int			builtin_export(char **cmd, t_list *env)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (export_check_input(cmd[i]) == 1)
			export_update_env(cmd[i], env);
		i++;
	}
	if (i == 1)
		export_sort_env(env);
	return (1);
}
