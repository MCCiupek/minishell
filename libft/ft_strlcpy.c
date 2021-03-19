/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:47:31 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 11:03:12 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = -1;
	if (!dest || !src)
		return (0);
	while (++i < size)
	{
		if (!src[i])
		{
			dest[i] = '\0';
			break ;
		}
		if (i == size - 1)
		{
			dest[i] = '\0';
			break ;
		}
		dest[i] = src[i];
	}
	while (src[i])
		i++;
	return (i);
}
