/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 22:25:00 by rmass             #+#    #+#             */
/*   Updated: 2021/02/23 20:34:17 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_value(t_env_var **list, char *key)
{
	t_env_var	*temp;
	t_env_var	*t;

	if (!(*list))
		return ;
	if (ft_strcmp((*list)->key, key))
	{
		*list = (*list)->next;
		return ;
	}
	temp = *list;
	while (temp->next)
	{
		if (ft_strcmp(temp->next->key, key))
		{
			t = temp->next;
			free_if_exist(temp->next->key);
			free_if_exist(temp->next->value);
			temp->next = temp->next->next;
			free(t);
			return ;
		}
		temp = temp->next;
	}
}

void	parse_env_vars(int i)
{
	int		fd;
	char	*buf;
	char	*line;
	char	*key;
	char	*value;

	buf = malloc(101);
	line = 0;
	fd = open("env_var", O_RDONLY);
	
	while (get_next_line(fd, buf, &line))
	{
		i = 0;
		while (line[i] != '=')
			i++;
		key = ft_strndup(line, i);
		value = ft_strdup(line + i + 1);
		add_var(key, value, &g_vars_list);
	}
}

void	save_env_vars(void)
{
	int			fd;
	t_env_var	*temp;

	fd = open("env_var", O_RDWR);
	temp = g_vars_list;
	while (temp)
	{
		write(fd, temp->key, ft_strlen(temp->key));
		write(fd, "=", 1);
		write(fd, temp->value, ft_strlen(temp->value));
		write(fd, "\n", 1);
		temp = temp->next;
	}
	close(fd);
}
