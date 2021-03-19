/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:21:14 by mciupek           #+#    #+#             */
/*   Updated: 2021/01/11 18:50:56 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float	ft_spaces(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] < '0' || str[i] > '9')
		&& str[i] != '-' && str[i] != '+' && str[i] != '.')
	{
		if (str[i] != '\t' && str[i] != '\n' && str[i] != '\v' &&
			str[i] != '\f' && str[i] != '\r' && str[i] != ' ')
			return (-1);
		i++;
	}
	return (i);
}

float			ft_atof(const char *str)
{
	int		i;
	float	j;
	int		signe;
	float	nb;

	if ((i = ft_spaces(str)) == -1)
		return (0);
	signe = 1;
	nb = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			signe = signe * -1;
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (str[i++] - '0');
	if (str[i++] == '.')
	{
		j = 10;
		while (str[i] >= '0' && str[i] <= '9')
		{
			nb += (str[i] - '0') / j;
			j *= 10;
			i++;
		}
	}
	return (signe * nb);
}
