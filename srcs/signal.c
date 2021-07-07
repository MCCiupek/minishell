/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:24:26 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:24:28 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int sig)
{
	(void)sig;
	signal(SIGINT, ctrl_c_handler);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ctrl_bs_handler(int sig)
{
	signal(SIGQUIT, ctrl_bs_handler);
	if (!kill(g_gbl.pid, sig))
		printf("Quit: 3\n");
}

void	set_sig(void)
{
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_bs_handler);
}

void	term_on(void)
{
	struct termios	t_termios;

	if (tcgetattr(0, &t_termios) == -1)
		return ;
	t_termios.c_lflag &= ~(ICANON);
	t_termios.c_lflag &= ~(ECHO);
	t_termios.c_lflag &= ~(ISIG);
	if (tcsetattr(0, 0, &t_termios) == -1)
		return ;
}

void	term_off(void)
{
	struct termios	t_termios;

	if (tcgetattr(0, &t_termios) == -1)
		return ;
	t_termios.c_lflag |= (ICANON);
	t_termios.c_lflag |= (ECHO);
	t_termios.c_lflag |= (ISIG);
	if (tcsetattr(0, 0, &t_termios) == -1)
		return ;
}
