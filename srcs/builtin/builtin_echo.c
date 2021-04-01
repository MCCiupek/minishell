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

void	built_in_exit(void)
{
	printf("%s", "exit\n");
	exit(EXIT_SUCCESS);
}