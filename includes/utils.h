/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:23:44 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/13 16:23:46 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "env.h"

int		ft_putchar(int n);
char	**lst_to_array(t_list *env);
void	free_t_cmd(void *ptr);

#endif
