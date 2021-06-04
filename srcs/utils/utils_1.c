/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:24:20 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/13 16:24:21 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putchar(int n)
{
	char	c;

	c = (char)n;
	write(1, &c, 1);
	return (1);
}

char	**lst_to_array(t_list *env)
{
	t_list	*tmp;
	char	**tab;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(env);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		error(MEM_ERR);
	tmp = env;
	tab[0] = NULL;
	while (tmp)
	{
		tab[i] = tmp->content;
		tmp = tmp->next;
		i++;
		tab[i] = NULL;
	}
	return (tab);
}

void	free_t_cmd(void *ptr)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = (t_cmd *)ptr;
	while (cmd->cmd[i])
		free(cmd->cmd[i++]);
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->in)
		free(cmd->in);
	if (cmd->out)
		free(cmd->out);
	free(cmd);
}
