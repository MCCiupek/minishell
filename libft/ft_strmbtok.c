/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmbtok.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 15:55:37 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/31 15:55:39 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void        init(char *str, char **token, char **lead)
{
    if (str)
	{
		*token = str;
		*lead = str;
	}
	else
	{
		*lead = *token;
		if (!**token)
			*lead = NULL;
	}
}

char		*ft_strmbtok(char *str, char *sep, char *quotes, int redir)
{
	static char	*token;
	char		*lead;
	char		*block;
	char		c;
	int			i;
	int			j;

	i = 0;
	j = 0;
    init(str, &token, &lead);
	while (*token)
	{
		if (!i && redir)
		{
			if (ft_strchr("<>", *token))
			{
				c = *token;
				i = -1;
				token++;
				if (c == '>' && *token == c)
					token++;
				while (ft_strchr(sep, *token))
					token++;
				continue ;
			}
		}
		if (i == 1)
		{
			if (quotes[j] == *token)
				i = 0;
			token++;
			continue ;
		}
		if ((block = ft_strchr(quotes, *token)))
		{
			i = 1;
			j = block - quotes;
			token++;
			continue ;
		}
		if (ft_strchr(sep, *token))
		{
			*token = '\0';
			token++;
			break ;
		}
		token++;
	}
	return (lead);
}
