/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 15:07:57 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 10:53:52 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(long n)
{
	size_t	i;

	i = n >= 0 ? 1 : 2;
	n = n >= 0 ? n : -n;
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	long	nb;
	char	*res;
	size_t	len;

	nb = (long)n;
	len = ft_nbrlen(nb);
	if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	res[0] = nb ? '-' : '0';
	res[len] = '\0';
	nb = n >= 0 ? nb : -nb;
	while ((nb * 10) / 10)
	{
		res[--len] = '0' + nb % 10;
		nb = nb / 10;
	}
	return (res);
}
