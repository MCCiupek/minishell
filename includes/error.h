/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:11:21 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/23 14:11:22 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

typedef enum	e_err
{
	ERRNO_TO_STR = -1,
	UKN_ERR,
    RD_ERR,
    CMD_ERR,
    PWD_ERR,
    CD_ERR
}				t_err;

typedef struct	s_error
{
	t_err	u_id;
	char	*msg;
}				t_error;

void			error(t_err raised);

#endif