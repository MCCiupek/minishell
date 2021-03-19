/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:40:11 by mciupek           #+#    #+#             */
/*   Updated: 2021/01/12 16:38:42 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *newl)
{
	t_list	*last_elem;

	if (!(*alst))
	{
		(*alst) = newl;
		return ;
	}
	if (alst && newl)
	{
		last_elem = ft_lstlast(*alst);
		last_elem->next = newl;
	}
}
