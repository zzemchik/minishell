/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 16:43:02 by rmass             #+#    #+#             */
/*   Updated: 2021/03/23 14:19:27 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*str_cpy;
	size_t	i;

	if (str == 0)
		return (0);
	i = ft_strlen(str);
	if (!(str_cpy = (char *)malloc(i + 1)))
		exita(0);
	str_cpy[i] = 0;
	i = 0;
	while (*str != 0)
	{
		str_cpy[i] = *str;
		i++;
		str++;
	}
	return (str_cpy);
}

char	*find_new_line(char *buff)
{
	int i;

	i = -1;
	while (buff[++i] != 0)
		if (buff[i] == '\n')
		{
			buff[i] = '\0';
			return (ft_strdup(&buff[i + 1]));
		}
	return (0);
}

void	print_list(t_list *list)
{
	while (list)
	{
		ft_putstr("\"");
		ft_putstr(list->data);
		ft_putstr("\"");
		list = list->next;
		if (list)
			ft_putstr(" -> ");
	}
	ft_putstr("\n");
}

void	skip(t_list **list)
{
	if (!list || !(*list))
		return ;
	while ((*list)->next && !ft_strcmp((*list)->next->data, "|") && \
	!ft_strcmp((*list)->next->data, ";"))
		free_one_list(list);
}

void	print_error(char *argv)
{
	ft_putstr("minishell: ");
	ft_putstr(argv);
	ft_putstr("\n");
	ft_putstr(strerror(errno));
	ft_putstr("\n");
}
