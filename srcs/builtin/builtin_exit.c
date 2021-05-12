/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:51:35 by mciupek           #+#    #+#             */
/*   Updated: 2021/05/12 16:51:38 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void		builtin_exit(char **builtin, t_list *env, t_list *hist, int silence, int ret)
{
	int	i;

	i = 0;
	if (builtin && array_len(builtin) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERROR);
		return ;
	}
	if (builtin && array_len(builtin) > 1 && str_isdigit(builtin[1]))
		ret = ft_atoi(builtin[1]);
	if (!silence)
		printf("exit\n");
	while (builtin && builtin[i])
	{
		free(builtin[i]);
		builtin[i++] = NULL;
	}
	if (env)
		ft_lstclear(&env, free);
	term_off();
	if (hist)
		ft_lstclear(&hist, free);
	exit(ret);
}
