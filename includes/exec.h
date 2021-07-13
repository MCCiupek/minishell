/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 09:32:41 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/26 09:32:43 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_params
{
	t_list	*cmds;
	t_list	*env;
	t_list	*hist;
}				t_params;

int		ft_err(t_cmd *cmd, int exit, int err);
int		ft_child(t_cmd *cmd, t_list *env);
int		ft_parent(t_cmd *cmd);
void	init_fds(int *fdin, int *fdout);
void	reset_fds(int fd[2]);
void	ft_wait(int nb_wait);
int		ft_pipe(t_list **cmds, t_params *params, char *line);
int		ft_exec(t_cmd *cmd, t_list *env);
int		exec_cmds(t_params *params, char *line);
int		get_absolute_path(char **cmd, t_list *env);
int		get_fd(t_cmd *cmd, int mode, int tmp, int fd);
int		open_close_fds(t_cmd *cmd, int fd[2], int tmp[2]);
int		open_close_fd(t_cmd *cmd);

#endif
