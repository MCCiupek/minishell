/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:58:43 by lkonig            #+#    #+#             */
/*   Updated: 2021/07/13 14:58:45 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_cd(char *s, int i)
{
	g_gbl.exit = 1;
	ft_putstr_fd("minishell: cd: ", STDERROR);
	ft_putstr_fd(s, STDERROR);
	if (i == 0)
		ft_putstr_fd("error retrieving current directory: getcwd: cannot access \
			parent directories: No such file or directory\n", STDERROR);
	if (i == 1)
		ft_putstr_fd(": No such file or directory\n", STDERROR);
	if (i == 2)
		ft_putstr_fd(" not set\n", STDERROR);
	return (i > 0);
}
