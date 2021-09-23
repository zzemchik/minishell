#include "minishell.h"

void			just_do_it(t_list **list, t_stack **stack, \
							void (*f)(t_list **list))
{
	int	pid;

	g_flag = 1;
	pid = fork();
	if (!pid)
	{
		if (f)
			f(list);
		exit(g_ret_value);
	}
	push(stack, pid);
	skip(list);
}

static int		find_arrow_ret(t_list *list, t_pair *pair)
{
	if (list->next == 0)
	{
		pair->first = -2;
		return (1);
	}
	if (ft_strcmp(list->next->data, ">") == 1 || \
	ft_strcmp(list->next->data, ">>") == 1 || \
	ft_strcmp(list->next->data, "<") == 1 || \
	ft_strcmp(list->next->data, "|") == 1 || \
	ft_strcmp(list->next->data, "/") == 1 || \
	ft_strcmp(list->next->data, "*") == 1 || \
	ft_strcmp(list->next->data, "(") == 1 || \
	ft_strcmp(list->next->data, ")") == 1 || \
	ft_strcmp(list->next->data, ";") == 1)
	{
		pair->first = -3;
		return (1);
	}
	return (0);
}

static t_pair	find_arrow_help(t_list *list)
{
	t_pair	pair;

	pair.first = -1;
	pair.second = 0;
	if (ft_strcmp(list->data, ">") == 1 || ft_strcmp(list->data, ">>") == 1 \
	|| ft_strcmp(list->data, "<") == 1)
	{
		if (list->next && list->next->data && list->next->data[0] == 0)
		{
			pair.first = -2;
			return(pair);
		}
		if (find_arrow_ret(list, &pair))
			return (pair);
		if (ft_strcmp(list->data, "<") == 1)
		{
			pair.second = 1;
			pair.first = open(list->next->data, O_RDWR, S_IREAD | S_IWRITE);
			if (pair.first == -1)
				pair.first = -4;
		}
		else if (ft_strcmp(list->data, ">>") == 1)
			pair.first = open(list->next->data, O_RDWR | O_APPEND \
			| O_CREAT, S_IREAD | S_IWRITE);
		else
			pair.first = open(list->next->data, O_RDWR | O_TRUNC \
			| O_CREAT, S_IREAD | S_IWRITE);
	}
	return (pair);
}

char			*find_arrow_loop(t_list **list, t_pair *pair, \
									int *fd_in, int *fd_out)
{
	while (*list && (ft_strcmp((*list)->data, "|") == 0))
	{
		*pair = find_arrow_help(*list);
		if (pair->first == -2)
			return (0);
		else if (pair->first == -3 || pair->first == -4)
			return ((*list)->next->data);
		if (pair->first > 0)
		{
			if (pair->second == 1)
			{
				fd_out[pair->first] = pair->first;
				g_out = pair->first;
			}
			else
			{
				fd_in[pair->first] = pair->first;
				g_in = pair->first;
			}
		}
		(*list) = (*list)->next;
	}
	return ("}{()ГlA");
}

char			*find_arrow(t_list *list, int j, char *str)
{
	int		fd_in[1024];
	int		fd_out[1024];
	t_pair	pair;

	g_in = 1;
	g_out = 0;
	while (++j < 1024)
	{
		fd_in[j] = 0;
		fd_out[j] = 0;
	}
	j = 1;
	str = find_arrow_loop(&list, &pair, fd_in, fd_out);
	if (!ft_strcmp(str, "}{()ГlA"))
		return (str);
	while (++j < 1024)
	{
		if (fd_in[j] != 0 && j != g_in)
			close(fd_in[j]);
		if (fd_out[j] != 0 && j != g_out)
			close(fd_out[j]);
	}
	dup2(g_in, 1);
	dup2(g_out, 0);
	return ("kak kakat");
}
