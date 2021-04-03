/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 20:10:21 by ivan              #+#    #+#             */
/*   Updated: 2021/04/03 21:01:33 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		give_pipe(t_list *list, int ***pipefd)
{
	int i;

	i = 0;
	while (list)
	{
		if (ft_strcmp(list->data, "|"))
			i++;
		list = list->next;
	}
	*pipefd = malloc((i + 1) * sizeof(int *));
	(*pipefd)[i] = 0;
	while (--i >= 0)
		(*pipefd)[i] = malloc(2 * sizeof(int));
	while ((*pipefd)[++i])
		pipe((*pipefd)[i]);
}

void		free_pipe(int ***pipefd)
{
	int	i;

	i = -1;
	while (*pipefd && (*pipefd)[++i])
	{
		close((*pipefd)[i][0]);
		close((*pipefd)[i][1]);
		free((*pipefd)[i]);
	}
	if (*pipefd)
		free(*pipefd);
}

void		find_tilda(t_list *list)
{
	char *tmp;

	while (list)
	{
		if (list->data[0] == '~' && (list->data[1] == '/' \
		|| list->data[1] == 0))
		{
			tmp = list->data;
			list->data = ft_strjoin(get_value("HOME", g_vars_list), \
			list->data + 1);
			free(tmp);
		}
		list = list->next;
	}
}

int			cheker_kalla(t_list **list)
{
	struct stat	buff;
	char		**path;
	int			i;
	char		*data;

	data = (*list)->data;
	path = standart_split(get_value("PATH", g_vars_list), ':');
	i = -1;
	while (path && path[++i])
	{
		str_new(&(path[i]), ft_strjoin(path[i], "/"));
		(*list)->data = ft_strjoin(path[i], data);
		if (stat((*list)->data, &buff) == 0)
		{
			free_if_exist(data);
			free_path(path);
			return (1);
		}
		free_if_exist((*list)->data);
	}
	(*list)->data = data;
	free_path(path);
	return (0);
}

void		kill_arrow(t_list **list_new, int flag, t_list *tmp)
{
	int i;

	i = 0;
	if ((ft_strcmp((*list_new)->data, ">>") || \
		ft_strcmp((*list_new)->data, ">")) &&
		(*list_new)->next->next && \
		ft_strcmp((*list_new)->next->next->data, "|"))
		i = 1;
	while (*list_new)
	{
		ft_lstadd_back(&tmp, ft_lstnew(ft_strdup((*list_new)->data)));
		free_one_list(list_new);
	}
	free_full_list(list_new);
	(*list_new) = 0;
	kill_arrow_help(&tmp, flag, list_new, i);
	free_full_list(&tmp);
}
