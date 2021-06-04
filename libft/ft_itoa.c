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

	i = 1;
	if (n < 0)
	{
		i = 2;
		n = -n;
	}
	while (n / 10)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*res;
	size_t	len;

	nb = (long)n;
	len = ft_nbrlen(nb);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[0] = '-';
	if (!nb)
		res[0] = '0';
	res[len] = '\0';
	if (n < 0)
		nb = -nb;
	while ((nb * 10) / 10)
	{
		res[--len] = '0' + nb % 10;
		nb = nb / 10;
	}
	return (res);
}
