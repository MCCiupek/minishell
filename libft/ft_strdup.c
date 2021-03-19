/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:33:12 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/18 20:22:08 by mcciupek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char *tab;

	tab = (char *)malloc(sizeof(*src) * (ft_strlen(src) + 1));
	if (tab)
	{
		ft_strlcpy(tab, src, ft_strlen(src) + 1);
		return (tab);
	}
	return (NULL);
}
