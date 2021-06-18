/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:03:18 by mciupek           #+#    #+#             */
/*   Updated: 2021/05/12 16:03:20 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

typedef struct s_parent_env {
	char	*home;
	char	*path;
	char	*oldpwd;
	char	*pwd;
	char	*shlvl;
}				t_parent_env;

t_parent_env	ft_parent_env(void);
t_list			*dup_env(char **envp);
int				is_in_env(char *s, t_list *env, int i);
void			add_env_var(t_list **env, char *var);
char			*get_env_var(char *var, t_list *env);
char			*replace(char *s, int i, t_list *env, int err);
char			*replace_env_var(char *cmd, char *quotes, t_list *env, int err);
int				replace_in_cmd(t_cmd *cmd, char *quotes, t_list *env);

#endif
