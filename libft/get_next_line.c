/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:02:09 by mcciupek          #+#    #+#             */
/*   Updated: 2021/01/11 17:49:21 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_err(int fd, char *buf, char **line)
{
	int	ret;

	ret = read(fd, buf, BUFFER_SIZE);
	buf[ret] = 0;
	if (fd < 0 || !line || BUFFER_SIZE < 1 || ret == -1)
	{
		free(buf);
		return (-1);
	}
	return (ret);
}

static int	ft_read(int fd, char *buf, t_line *nl, int ret)
{
	char	*tmp;

	while (ret >= 0)
	{
		tmp = ft_gnl_strjoin(nl->txt, buf);
		if (!tmp)
			return (-1);
		if (nl->count++)
			free(nl->txt);
		nl->txt = ft_gnl_strldup(tmp, ft_gnl_strlen(tmp));
		if (!nl->txt)
			return (-1);
		free(tmp);
		if (ft_gnl_strchr(buf, '\n') || !ret)
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = 0;
	}
	free(buf);
	if (ret < 0)
		return (-1);
	return (ret);
}

static int	ft_reset(t_line *nl, char **line, int b_line, int ret_val)
{
	if (b_line)
	{
		*line = (char *)malloc(sizeof(char) * 1);
		if (!(*line))
			ret_val = -1;
		else
			*(line[0]) = 0;
	}
	free(nl->txt);
	nl->count = 0;
	return (ret_val);
}

static int	ft_stock(t_line *nl, char **line)
{
	int		i;
	int		eof;
	char	c;

	i = -1;
	eof = 1;
	c = '\0';
	while (nl->txt && *(nl->txt + ++i))
	{
		c = *(nl->txt + i);
		if (c == '\n')
			break ;
	}
	if (c == '\n')
		eof = 0;
	*line = ft_gnl_strldup(nl->txt, i);
	if (!(*line))
		return (-1);
	if (!eof)
		if (ft_tmp(nl, i) < 0)
			return (-1);
	return (eof == 0);
}

int			get_next_line(int fd, char **line)
{
	char			*buf;
	static t_line	nl;
	int				err;

	if (!nl.count)
		nl.txt = NULL;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	err = ft_err(fd, buf, line);
	if (err == -1)
		return (-1);
	err = ft_read(fd, buf, &nl, err);
	if (err == -1)
		return (ft_reset(&nl, line, 1, -1));
	err = ft_stock(&nl, line);
	if (!err)
		ft_reset(&nl, line, 0, err);
	return (err);
}
