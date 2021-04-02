/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:32:00 by fcivetta          #+#    #+#             */
/*   Updated: 2021/03/26 17:05:13 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_built_in(char *cmd)
{
	const char	*built_in[] = {"pwd", "cd", "env", "exit", "unset", "export", "echo", NULL}; // A mettre dans un tableau dans la structure principale
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	while (built_in[i])
	{
		if (!ft_strncmp(cmd, built_in[i], ft_strlen(cmd)))
			return(1);
		i++;
	}
	return (0);
}

void	exec_built_in(char **built_in, t_list *env)
{
	if(!ft_strncmp(built_in[0], "pwd", 3))
		printf("%s\n", built_in_pwd());
	else if (!ft_strncmp(built_in[0], "cd", 2)) // Mettre + 1 pour le \0 ?? Plus safe mais verifier si pas de segfault
		built_in_cd(built_in[1], env);
	else if (!ft_strncmp(built_in[0], "env", 3))
		built_in_env(env);
    else if (!ft_strncmp(built_in[0], "echo", 4))
        built_in_echo(built_in, env);
	else if (!ft_strncmp(built_in[0], "exit", 4))
		built_in_exit();
//	else if (!ft_strncmp(built_in[0], "export", 6)   A suivre sur le meme principe
//		built_in_export(built_in, env);
}