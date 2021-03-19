/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:44:22 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/19 18:41:55 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	while ((p1 || p2) && size--)
	{
		if (*((unsigned char *)p1) != *((unsigned char *)p2))
			return (*((unsigned char *)p1) - *((unsigned char *)p2));
		p1++;
		p2++;
	}
	return (0);
}
