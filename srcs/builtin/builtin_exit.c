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

void		builtin_exit(t_list *c, t_list *env, t_list *hist, int sil, int r)
{
	int	i;

	i = 0;
	if (((t_cmd *)c->content)->cmd && \
		array_len(((t_cmd *)c->content)->cmd) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERROR);
		return ;
	}
	if (((t_cmd *)c->content)->cmd \
		&& array_len(((t_cmd *)c->content)->cmd) > 1 \
		&& str_isdigit(((t_cmd *)c->content)->cmd[1]))
		r = ft_atoi(((t_cmd *)c->content)->cmd[1]);
	if (!sil)
		printf("exit\n");
	ft_lstclear(&c, free_t_cmd);
	if (env)
		ft_lstclear(&env, free);
	term_off();
	if (hist)
		ft_lstclear(&hist, free);
	exit(r);
}
