/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:15:19 by mciupek           #+#    #+#             */
/*   Updated: 2021/01/12 14:18:12 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *newl)
{
	if (!(*alst))
	{
		(*alst) = newl;
		return ;
	}
	if (alst && newl)
	{
		newl->next = *alst;
		*alst = newl;
	}
}
