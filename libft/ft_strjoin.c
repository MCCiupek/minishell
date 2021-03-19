/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:49:43 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 09:54:25 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	l1;
	size_t	l2;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if ((tab = malloc(sizeof(char *) * (1 + l1 + l2))))
	{
		i = ft_strlcpy(tab, s1, l1 + 1);
		i = ft_strlcpy(tab + l1, s2, l2 + 1);
		return (tab);
	}
	return (NULL);
}
