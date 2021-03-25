/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 14:11:21 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/24 15:04:47 by fcivetta         ###   ########.fr       */
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
    CD_ERR,
    MEM_ERR,
    FRK_ERR,
    SHL_ERR,
    PATH_ERR
}				t_err;

typedef struct	s_error
{
	t_err	u_id;
	char	*msg;
}				t_error;

void			error(t_err raised);

#endif