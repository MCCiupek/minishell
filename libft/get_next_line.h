/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcciupek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 11:47:34 by mcciupek          #+#    #+#             */
/*   Updated: 2021/01/11 17:50:22 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFFER_SIZE 2048

typedef struct	s_line
{
	int		count;
	char	*txt;
}				t_line;

int				ft_tmp(t_line *nl, int i);
int				get_next_line(int fd, char **line);
int				ft_gnl_strlen(char *str);
int				ft_gnl_strchr(char *str, int ch);
size_t			ft_gnl_strlcpy(char *dest, char *src, size_t size);
char			*ft_gnl_strldup(char *src, size_t size);
char			*ft_gnl_strjoin(char *s1, char *s2);

#endif
