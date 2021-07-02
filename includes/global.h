/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:48:09 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/19 13:48:11 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "minishell.h"

typedef struct s_gbl
{
	pid_t	pid;
    int		exit;
}				t_gbl;

#endif