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

typedef struct s_quotepos{
	int	quote_pos_open;
	int	quote_pos_close;
	int	in_quote;
	int	out_quote;
	int	is_env;
	int	nb_open;
	int	nb_close;
}				t_quotepos;

int		is_built_in(char *cmd);
int		exec_built_in(char **built_in, t_list *env);

int		built_in_cd(char *path, t_list *env);
int		built_in_cd_nbargs(char **built_in, t_list *env);
int		print_error_cd(char *s, int i);

int		built_in_pwd(void);
char	*get_pwd(void);
char	*get_pwd_env(t_list *env);
int		built_in_env(t_list *env);

void	ft_exit(t_list *c, t_list *env, t_list *hist);
void	builtin_exit(t_list *cmds, t_list *env, t_list *hist);

int		builtin_export(char **cmd, t_list *env);
void	export_sort_env(t_list *env);
int		compare_len(int len, char *b);
void	check_space(void *s);
void	export_new_element(t_list *env, char *newenv);

int		builtin_unset(char **builtin, t_list **env);
int		array_len(char **a);
int		cmp_unsetval(char *s1, char *s2);
t_list	*unset_val(t_list **env, t_list	*env_cp);
int		check_unset_builtin(char *builtin);
t_list	*unset_env(t_list **env, char *searched);

int		built_in_echo(char **cmd, t_list *env);
int		replace_and_print(char *s, t_list *env, int skip_spaces, int i);
int		is_n(char *s);
char	*copy_begin(char *s, int k);
void	print_len(char *s, int k);
int		is_outside_quote(char *s);
void	init_quotepos(t_quotepos *pos);
void	update_openquote(t_quotepos *pos, int k);
void	update_closequote(t_quotepos *pos, int k);
void	update_content(t_quotepos *pos);
int		is_outside(t_quotepos pos);

#endif
