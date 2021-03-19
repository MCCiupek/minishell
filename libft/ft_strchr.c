/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:09:46 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/17 15:09:53 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int ch)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ch)
			return ((char *)&str[i]);
	if (ch)
		return (0);
	else
		return ((char *)&str[i]);
}
