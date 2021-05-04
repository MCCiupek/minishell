#include "minishell.h"

char	*history_up(int hist_pos, t_list *hist)
{
	t_list	*tmp;

    if (!hist)
		return ("\0");
	tmp = hist;
	while (hist_pos > 1 && tmp)
	{
		tmp = tmp->next;
		hist_pos--;
	}
    if (!tmp)
        return ("\0");
	ft_putstr_fd(tmp->content, STDOUT_FILENO);
	return (tmp->content);
}

char	*history_down(int hist_pos, t_list *hist)
{
	t_list	*tmp;

    if (hist_pos == 0)
        return("\0");
	if (!hist)
		return ("\0");
	tmp = hist;
	while (hist_pos > 1 && tmp)
	{
		tmp = tmp->next;
		hist_pos--;
	}
    if (!tmp)
        return ("\0");
	ft_putstr_fd(tmp->content, STDOUT_FILENO);
	return (tmp->content);
}

int		check_empty(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

t_list	*update_hist(char *line, t_list *hist)
{
	if (ft_strncmp(line, "\n", ft_strlen(line)) && ft_strncmp(line, "\0", ft_strlen(line)) && check_empty(line))
	{
        if (!hist || (hist && ft_strncmp(hist->content, line, ft_strlen(line))))
	    	ft_lstadd_front(&hist, ft_lstnew(line));
	}
	return (hist);
}

char		*access_history(char c, t_pos *pos, t_list *hist, char *line)
{
    if (c == 'u' && pos->hist < ft_lstsize(hist))
		pos->hist++;
	else if (c == 'd' && pos->hist > 0) 
		pos->hist--;
    if (c == 'u' && pos->hist > 0)
    {
        delete_to_replace(pos->curs);
		line = ft_strdup(history_up(pos->hist, hist));
    }
	else if (c == 'd' && pos->hist >= 0)
    {
        delete_to_replace(pos->curs);
		line = ft_strdup(history_down(pos->hist, hist));
	}
    pos->line = ft_strlen(line);
	pos->curs = pos->line;
	return (line);
}