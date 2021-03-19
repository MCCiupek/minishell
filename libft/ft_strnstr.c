/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 14:10:03 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 11:53:27 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t size)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (!*s2)
		return ((char *)s1);
	while (s1[i] && i < size)
	{
		j = 0;
		while (s1[i + j] == s2[j] && i + j < size)
			if (!s2[++j])
				return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
