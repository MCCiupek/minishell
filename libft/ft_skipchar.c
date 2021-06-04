/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 14:24:19 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/12 14:24:24 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skipchar(char *s, int i)
{
	char	*copy;
	char	*tmp;

	if (s)
	{
		if (i >= ft_strlen(s))
			return (s);
		tmp = (char *)malloc(sizeof(s) * (i + 1));
		if (!tmp)
			return (NULL);
		ft_strlcpy(tmp, s, i + 1);
		if (i < ft_strlen(s) - 1)
			copy = ft_strjoin(tmp, &s[i + 1]);
		else
			copy = ft_strdup(tmp);
		free(s);
		free(tmp);
		return (copy);
	}
	return (NULL);
}
