/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:08:11 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/23 10:43:57 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = ft_strlen(dest);
	j = 0;
	while(src[j])
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return(dest);
}