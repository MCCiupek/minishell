/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:05:10 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/12 19:05:11 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "env.h"

int		is_built_in(char *cmd);
void	exec_built_in(char **built_in, t_list *env);
void	built_in_cd(char *path, t_list *env);
void	built_in_cd_nbargs(char **built_in, t_list *env);
void	built_in_pwd(void);
void	built_in_env(t_list *env);
void	built_in_echo(char **cmd, t_list *env);
void	builtin_exit(t_list *cmds, t_list *env, t_list *hist,
		int silence, int ret);
void	builtin_unset(char **builtin, t_list *env);
int		builtin_export(char **cmd, t_list *env);
int		array_len(char **a);

#endif
