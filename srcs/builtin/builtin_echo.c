/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:37:36 by fcivetta          #+#    #+#             */
/*   Updated: 2021/03/25 17:41:15 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//#include <stdio.h>
/*
int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int	i;

	i = 0;
	if (!len)
		return (0);
	while ((s1[i] || s2[i]) && i < len)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}*/


void	built_in_echo(char **cmd)
{
	int		new_line;
	int		i;

	i = 1;
	new_line = 1;
	if (!cmd[i])
		return;
	if (!ft_strncmp(cmd[i], "-n", 3))
	{
		new_line = 0;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		i++;
		if(cmd[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}
/*
int		main(int argc, char **argv)
{
//	printf("%s", argv[1]);
	built_in_echo(argv);
}*/