/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:36:29 by lkonig            #+#    #+#             */
/*   Updated: 2021/06/09 14:36:31 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_prompt_pwd(char *s)
{
	char	*tmp_pwd;

	tmp_pwd = get_pwd();
	if (ft_strlen(s) == 0)
		s = ft_strdup(tmp_pwd);
	free(tmp_pwd);
	return (s);
}
