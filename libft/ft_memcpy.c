/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 19:41:59 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 10:54:23 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	void	*original_dest;

	if (!dest && !src)
		return (NULL);
	original_dest = dest;
	while (size--)
		ft_memset(dest++, *((unsigned char *)src++), 1);
	return (original_dest);
}
