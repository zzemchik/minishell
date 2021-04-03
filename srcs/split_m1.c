/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_m1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 23:25:34 by rnancee           #+#    #+#             */
/*   Updated: 2021/04/03 21:03:12 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strcmp_split(const char *str, const char *find)
{
	int i;

	i = -1;
	while (find[++i])
		if (str[i] != find[i])
			return (0);
	return (1);
}

char		*ft_split_2(t_list *list, char *str)
{
	char		*str_n;

	str_n = 0;
	if (ft_strcmp_split(ft_lstlast(list)->data, "|") && \
	!ft_strcmp_split((list)->data, "|"))
	{
		ft_putstr("> ");
		while (get_next_line_mini(0, &(str)))
		{
			str_new(&str, ft_strndup(str, ft_strlen(str) - 1));
			str_new(&str, ft_strtrim(str, " "));
			str_new(&str_n, ft_strjoin(str_n, str));
			if (str[ft_strlen(str) - 1] != '|')
				break ;
			ft_putstr("> ");
			free_if_exist(str);
		}
	}
	return (str_n);
}

void		exita(int code)
{
	free_vars_list(g_temp_vars_list);
	free_vars_list(g_vars_list);
	exit(code);
}
