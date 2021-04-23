/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:48:09 by mciupek           #+#    #+#             */
/*   Updated: 2021/03/19 13:48:11 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>

# ifdef LINUX
#  include <linux/limits.h> 
# endif

# include "../libft/libft.h"
# include "parsing.h"
# include "utils.h"
# include "builtin.h"
# include "error.h"
# include "env.h"

# define PATH_MAX 4096
# define FD_SIZE 256
# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define true 1
# define false 0
# define READ 0
# define WRITE 1
# define UP "\033[A"
# define DOWN "\033[B"
# define RIGHT "\033[C"
# define LEFT "\033[D"
# define CTRL_C "\003"
# define CTRL_D "\04"

#endif
