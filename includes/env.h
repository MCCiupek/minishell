/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcivetta <fcivetta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 15:58:37 by user42            #+#    #+#             */
/*   Updated: 2021/03/23 15:58:37 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct	s_parent_env {
	char	*home;
	char	*path;
	char	*oldpwd;
	char	*pwd;
	char	*shlvl;
}		t_parent_env;

typedef	struct	s_env {
	char		*var;
	struct s_env	*next;
	struct s_env	*first;
}		t_env;


t_parent_env	ft_parent_env(void);

#endif
