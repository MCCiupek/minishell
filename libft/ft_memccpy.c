/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:08:33 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/19 18:35:51 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int ch, size_t size)
{
	void	*original_dest;

	original_dest = dest;
	while (size--)
	{
		ft_memset(dest++, *((char *)src), 1);
		if (*((unsigned char *)src++) == (unsigned char)ch)
			return (dest);
	}
	return (NULL);
}
