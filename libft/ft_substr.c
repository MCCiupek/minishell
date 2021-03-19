/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:59:33 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 11:23:28 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = (unsigned int)ft_strlen(s);
	if (start < len_s)
	{
		if (!(res = (char *)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		ft_strlcpy(res, s + start, len + 1);
		return (res);
	}
	else
	{
		if (!(res = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	return (NULL);
}
