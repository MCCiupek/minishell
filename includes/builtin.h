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
void		exec_built_in(char **built_in, t_env *env);
void		built_in_cd(char *path, t_env *env);
char		*built_in_pwd(void);
void		built_in_env(t_env *env);
void        built_in_echo(char **cmd);

#endif
