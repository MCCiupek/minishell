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

static void	init(char *str, char **token, char **lead, int i[2])
{
	i[0] = 0;
	i[1] = 0;
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

static void	ft_block(int i[2], char **token, char *block, char *quotes)
{
	i[0] = 1;
	i[1] = block - quotes;
	(*token)++;
}

static int	ft_end_quote(int i[2], char **token, char *quotes)
{
	int	res;

	res = i[0];
	if (quotes[i[1]] == **token)
		res = 0;
	(*token)++;
	return (res);
}

char	*ft_strmbtok(char *str, char *sep, char *quotes, int redir)
{
	static char	*token;
	char		*lead;
	int			i[2];

	init(str, &token, &lead, i);
	while (*token)
	{
		if (!i[0] && redir && ft_strchr("<>", *token))
			i[0] = ft_redir(&token, sep);
		else if (i[0] == 1)
			i[0] = ft_end_quote(i, &token, quotes);
		else if (ft_strchr(quotes, *token))
			ft_block(i, &token, ft_strchr(quotes, *token), quotes);
		else if (ft_strchr(sep, *token))
		{
			*token++ = '\0';
			break ;
		}
		else
			token++;
	}
	return (lead);
}
