/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_without_char.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:24:37 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/24 09:51:11 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd_without_char(char *s, int fd, char c)
{
	if (!s || !fd || !c)
		return ;
	while (*((char *)s))
	{
		if (*((char *)s) != c)
			write(fd, s++, 1);
		else
			s++;
	}
}
