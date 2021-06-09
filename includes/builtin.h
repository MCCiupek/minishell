/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkonig <lkonig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:05:10 by lkonig            #+#    #+#             */
/*   Updated: 2021/05/12 19:05:11 by lkonig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "env.h"

int		is_built_in(char *cmd);
void	exec_built_in(char **built_in, t_list *env);
void	built_in_cd(char *path, t_list *env);
void	built_in_cd_nbargs(char **built_in, t_list *env);
void	built_in_pwd(void);
char	*get_pwd(void);
void	built_in_env(t_list *env);
void	built_in_echo(char **cmd, t_list *env);
void	ft_exit(t_list *c, t_list *env, t_list *hist, int r);
void	builtin_exit(t_list *cmds, t_list *env, t_list *hist, int r);
int		builtin_export(char **cmd, t_list *env);
void	export_sort_env(t_list *env);
int		compare_len(int len, char *b);
void	check_space(void *s);
void	builtin_unset(char **builtin, t_list **env);
int		array_len(char **a);
int		cmp_unsetval(char *s1, char *s2);
t_list	*unset_val(t_list **env, t_list	*env_cp);
int		check_unset_builtin(char *builtin);
t_list	*unset_env(t_list **env, char *searched);
void	export_new_element(t_list *env, char *newenv);

#endif
