/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:33:50 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/26 13:34:10 by fcivetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "env.h"

int		is_built_in(char *cmd);
void		exec_built_in(char **built_in, t_list *env, t_list *hist, char *line);
void		built_in_cd(char *path, t_list *env);
void	    built_in_cd_nbargs(char **built_in, t_list *env);
void		built_in_pwd(void);
void		built_in_env(t_list *env);
void        built_in_echo(char **cmd, t_list *env);
void	    builtin_exit(char **builtin, t_list *env, t_list *hist, int silence, int ret);
void	    builtin_unset(char **builtin, t_list *env);
int		builtin_export(char **cmd, t_list *env);

#endif
