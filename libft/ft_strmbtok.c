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

static void	init(char *str, char **token, char **lead)
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

static int	ft_redir(char **token, char *sep)
{
	char	c;

	c = **token;
	(*token)++;
	if (c == '>' && **token == c)
		(*token)++;
	while (ft_strchr(sep, **token))
		(*token)++;
	return (-1);
}

char		*ft_strmbtok(char *str, char *sep, char *quotes, int redir)
{
	static char	*token;
	char		*lead;
	char		*block;
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
				i = ft_redir(&token, sep);
				continue ;
			}
		}
		if (i == 1)
		{
			if (quotes[j] == *token++)
				i = 0;
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
			*token++ = '\0';
			break ;
		}
		token++;
	}
	return (lead);
}
