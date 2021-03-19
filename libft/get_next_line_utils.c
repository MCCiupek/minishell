/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:52:40 by mcciupek          #+#    #+#             */
/*   Updated: 2021/01/11 17:50:25 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_gnl_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

static void	*ft_gnl_memcpy(char *dest, char *src, size_t size)
{
	while (size--)
		*dest++ = *src++;
	return (NULL);
}

char		*ft_gnl_strldup(char *src, size_t size)
{
	char	*tab;

	tab = (char *)malloc(sizeof(char) * (size + 1));
	if (tab)
	{
		ft_gnl_memcpy(tab, src, size);
		tab[size] = 0;
		return (tab);
	}
	return (NULL);
}

char		*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*tab;
	size_t	l1;
	size_t	l2;

	l1 = ft_gnl_strlen(s1);
	l2 = ft_gnl_strlen(s2);
	tab = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
	if (tab)
	{
		ft_gnl_memcpy(tab, s1, l1);
		ft_gnl_memcpy(tab + l1, s2, l2);
		tab[l1 + l2] = 0;
		return (tab);
	}
	return (NULL);
}

int			ft_gnl_strchr(char *str, int ch)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == ch)
			return (1);
	return (0);
}
