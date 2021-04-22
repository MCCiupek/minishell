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
//    int     i;

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

t_list	*update_hist(char *line, t_list *hist)
{
	char *tmp;
	t_list	*lst;
	
	if (ft_strncmp(line, "\n", ft_strlen(line)) && ft_strncmp(line, "\0", ft_strlen(line)))
	{
        if (!hist || (hist && ft_strncmp(hist->content, line, ft_strlen(line))))
        {
    		tmp = ft_strdup(line);
	    	ft_lstadd_front(&hist, ft_lstnew(tmp));
        }
	}
	lst = hist;
/*    int i = 1;
	printf("-----STATE OF HISTORY-----\n");
	while (lst)
	{
		printf("#%i %s\n", i, lst->content);
        i++;
		lst = lst->next;
	}
    printf("lstsize=%i\n", ft_lstsize(hist));
	printf("--------------------------\n"); */
	return (hist);
}