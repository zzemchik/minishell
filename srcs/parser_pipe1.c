#include "minishell.h"

void	kill_arrow_help(t_list **tmp, int flag, t_list **list_new, int i)
{
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->data, "|") == 1)
			flag = 1;
		if (flag == 0 && ((ft_strcmp((*tmp)->data, ">") == 1 \
		|| ft_strcmp((*tmp)->data, ">>") == 1) \
		|| (ft_strcmp((*tmp)->data, "<") == 1)))
		{
			if (i == 1)
			{
				ft_lstadd_back(&(*list_new), ft_lstnew(ft_strdup("sleep")));
				ft_lstadd_back(&(*list_new), ft_lstnew(ft_strdup("0")));
				i = 0;
			}
			free_one_list(tmp);
			free_one_list(tmp);
			continue;
		}
		ft_lstadd_back(&(*list_new), ft_lstnew(ft_strdup((*tmp)->data)));
		if (*tmp)
			free_one_list(tmp);
	}
}
