/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:51:38 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 12:04:38 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	if (!dest && !src)
		return (NULL);
	if (src > dest)
		ft_memcpy(dest, src, size);
	else
		while (size--)
			((unsigned char *)dest)[size] = ((unsigned char *)src)[size];
	return (dest);
}
