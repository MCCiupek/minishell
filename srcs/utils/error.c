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

int	export_print_error(char *err)
{
	ft_putstr_fd("minishell: export: « ", STDERROR);
	ft_putstr_fd(err, STDERROR);
	ft_putstr_fd(" » : not a valid identifier\n", STDERROR);
	return (0);
}

char	*get_error_msg(t_err raised)
{
	const char	*errors[] = {"Unknown error.",
		"Cannot read file.",
		"command not found",
		"Cannot execute pwd.",
		"Cannot execute cd.",
		"Allocation error.",
		"Fork error.",
		"Shell error",
		"execution failed",
		"too many arguments",
		"numeric argument required",
		"syntax error near unexpected token ",
		"Path error.",
		"No such file or directory"};

	if (raised != ERRNO_TO_STR)
		return ((char *)errors[raised]);
	return ((char *)strerror(errno));
}

int	print_error_str(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", STDERROR);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERROR);
		ft_putstr_fd(": ", STDERROR);
	}
	ft_putstr_fd(msg, STDERROR);
	free(msg);
	ft_putstr_fd("\n", STDERROR);
	return (0);
}

int	print_error(char *cmd, t_err raised)
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
	return (0);
}

void	error(t_err raised)
{
	print_error(NULL, raised);
	exit(EXIT_FAILURE);
}
