/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:30:51 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:30:53 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include "minishell.h"

void	ctrl_c_handler(int sig);
void	ctrl_bs_handler(int sig);
void	set_sig(void);
void	term_on(void);
void	term_off(void);

#endif
