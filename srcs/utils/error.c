/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:24:31 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/13 16:24:32 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_error	g_errors[] =
{
	{ UKN_ERR, "Unknown error." },
	{ RD_ERR, "Cannot read file." },
	{ CMD_ERR, "command not found" },
	{ PWD_ERR, "Cannot execute pwd." },
	{ CD_ERR, "Cannot execute cd." },
	{ MEM_ERR, "Allocation error."},
	{ FRK_ERR, "Fork error."},
	{ SHL_ERR, "Shell error"},
	{ EXEC_ERR, "execution failed"},
	{ PATH_ERR, "Path error."}
};

void		export_print_error(char *err)
{
	ft_putstr_fd("minishell: export: « ", STDERROR);
	ft_putstr_fd(err, STDERROR);
	ft_putstr_fd("» : identifiant non valable\n", STDERROR);
}

static char	*get_error_msg(t_err raised)
{
	if (raised != ERRNO_TO_STR)
		return (g_errors[raised].msg);
	return ((char *)strerror(errno));
}

void		print_error(char *cmd, t_err raised)
{
	char	*msg;

	ft_putstr_fd("minishell: ", STDERROR);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERROR);
		ft_putstr_fd(": ", STDERROR);
	}
	msg = get_error_msg(raised);
	ft_putstr_fd(msg, STDERROR);
	ft_putstr_fd("\n", STDERROR);
}

void		error(t_err raised)
{
	print_error(NULL, raised);
	exit(EXIT_FAILURE);
}
