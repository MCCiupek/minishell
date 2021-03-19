/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:53:18 by mciupek           #+#    #+#             */
/*   Updated: 2020/11/25 14:26:20 by mcciupek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int ch)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (!ch)
		return ((char *)&str[i]);
	while (i-- > 0)
		if (str[i] == ch)
			return ((char *)&str[i]);
	return (0);
}
