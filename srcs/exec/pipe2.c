/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:27:57 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:27:59 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds(int *fdin, int *fdout)
{
	*fdin = dup(STDIN);
	*fdout = dup(STDOUT);
}

void	reset_fds(int fd[2])
{
	dup2(fd[WRITE], STDOUT);
	dup2(fd[READ], STDIN);
}

void	ft_wait(int nb_wait)
{
	while (nb_wait--)
		if (wait(&g_gbl.exit) == g_gbl.pid)
		{	
			printf("exit = %d\t", g_gbl.exit);
			g_gbl.exit = WEXITSTATUS(g_gbl.exit);
			printf("exit = %d\n", g_gbl.exit);
		}
}
