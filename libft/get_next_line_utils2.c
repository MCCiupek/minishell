/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:52:40 by mcciupek          #+#    #+#             */
/*   Updated: 2021/01/11 17:50:25 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tmp(t_line *nl, int i)
{
	char	*tmp;

	tmp = ft_gnl_strldup(nl->txt + i + 1, ft_gnl_strlen(nl->txt) - i - 1);
	if (!tmp)
		return (-1);
	free(nl->txt);
	nl->txt = ft_gnl_strldup(tmp, ft_gnl_strlen(tmp));
	if (!nl->txt)
		return (-1);
	free(tmp);
	return (1);
}
