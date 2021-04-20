/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mciupek <mciupek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:01:23 by mciupek           #+#    #+#             */
/*   Updated: 2021/04/19 16:01:25 by mciupek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

int init_term(void)
{
    int ret;
    char *term_type;

    term_type = getenv("TERM");
    printf("Terminal type '%s'.\n", term_type);
    if (!term_type)
    {
        printf("TERM must be set (see 'env').\n");
        return -1;
    }
    ret = tgetent(NULL, term_type);
    if (ret == -1)
    {
        printf("Could not access to the termcap database..\n");
        return -1;
    }
    else if (!ret)
    {
        printf("Terminal type '%s' is not defined in termcap database (or have too few informations).\n", term_type);
        return -1;
    }
    int column_count = tgetnum("co");
    printf("Columns '%d'.\n", column_count);
    return 0;
}
