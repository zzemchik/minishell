#include "minishell.h"

void	str_new(char **str, char *new)
{
	char *tmp;

	tmp = *str;
	*str = new;
	free(tmp);
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path && path[++i])
		free_if_exist(path[i]);
	free(path);
}

char	*give_pwd(void)
{
	char	*value;
	t_list	*lst;

	lst = 0;
	value = get_value("PWD", g_vars_list);
	if (!value)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup("cd")));
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(".")));
		command_cd(&lst, 0);
		free_full_list(&lst);
		value = get_value("PWD", g_vars_list);
	}
	return (value);
}
