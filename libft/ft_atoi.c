/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:21:14 by mciupek           #+#    #+#             */
/*   Updated: 2021/01/11 17:07:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] < '0' || str[i] > '9') && str[i] != '-' && str[i] != '+')
	{
		if (str[i] != '\t' && str[i] != '\n' && str[i] != '\v' &&
			str[i] != '\f' && str[i] != '\r' && str[i] != ' ')
			return (-1);
		i++;
	}
	return (i);
}

int			ft_atoi(const char *str)
{
	int	i;
	int	signe;
	int	nb;

	i = ft_spaces(str);
	if (i == -1)
		return (0);
	signe = 1;
	nb = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	nb = signe * nb;
	return (nb);
}
