/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 14:02:22 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/18 17:05:43 by mcciupek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mem, int ch, size_t size)
{
	while (size--)
	{
		if (*((char *)mem) == (char)ch)
			return ((void *)mem);
		mem++;
	}
	return (0);
}
