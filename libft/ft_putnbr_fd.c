/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:37:07 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/23 16:36:09 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_write_nbr(int nb, int fd)
{
	int	r;

	r = nb % 10;
	if (nb / 10)
		ft_write_nbr(nb / 10, fd);
	r = r + '0';
	ft_putchar_fd(r, fd);
}

void		ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n = -n;
		}
		ft_write_nbr(n, fd);
	}
}
