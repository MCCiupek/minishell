/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 13:33:50 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/23 13:33:52 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		is_built_in(char *cmd);
void		exec_built_in(char **built_in);
void		built_in_cd(char *path);
void		*built_in_pwd(void);

#endif
