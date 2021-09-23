#include "minishell.h"

void	command_echo(t_list **list)
{
	int		flag_n;

	flag_n = 0;
	free_one_list(list);
	while ((*list) && ft_strcmp((*list)->data, "-n") == 1 && (flag_n = 1))
		free_one_list(list);
	while (*list)
	{
		if (ft_strcmp((*list)->data, "|") || ft_strcmp((*list)->data, ";") || \
		ft_strcmp((*list)->data, ">") || ft_strcmp((*list)->data, ">>") || \
		ft_strcmp((*list)->data, "<"))
			break ;
		ft_putstr((*list)->data);
		if ((*list)->next && !(ft_strcmp((*list)->next->data, "|") \
		|| ft_strcmp((*list)->next->data, ";")))
			ft_putstr(" ");
		free_one_list(list);
	}
	if (flag_n == 0)
		ft_putstr("\n");
	g_ret_value = 0;
}
