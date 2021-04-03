/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_m.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:55:10 by rnancee           #+#    #+#             */
/*   Updated: 2021/04/03 23:59:07 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		many_operators(t_list **list, char *find, t_pair *p, char *str)
{
	if (p->first != p->second)
		ft_lstadd_back(list, \
		ft_lstnew(ft_strndup(&str[p->second], p->first - p->second)));
	if (*find != ' ')
		ft_lstadd_back(list, ft_lstnew(ft_strdup(find)));
	while (str[p->second] == *find)
		p->second++;
	return (-2);
}

static int		what_i_seek(t_list **my_list, char *find, t_pair *p, char *str)
{
	int i;
	int	f;

	i = 0;
	f = 0;
	if (*find == ';' || *find == '|')
	{
		while (++f < 3)
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == ';' || str[i] == '|')
				return ((*find == ';') ? many_operators(my_list, ";;", p, str) \
				: many_operators(my_list, "||", p, str));
				i = p->first + 1;
		}
	}
	if (p->first != p->second)
		ft_lstadd_back(my_list, \
		ft_lstnew(ft_strndup(&str[p->second], p->first - p->second)));
	if (*find != ' ')
		ft_lstadd_back(my_list, ft_lstnew(ft_strdup(find)));
	p->second = p->first + ft_strlen(find);
	return (!(ft_strlen(find) == 1));
}

static int		ft_split_norm(t_list **my_list, char *str, t_pair *p, int er, t_pair pair)
{
	if (pair.first % 2 == 0 && pair.second % 2 == 0)
	{
		if (ft_strcmp_split(&str[p->first], ">>>>") == 1)
			er = many_operators(my_list, ">>>>", p, str);
		else if (ft_strcmp_split(&str[p->first], ">>>") == 1)
			er = many_operators(my_list, ">>>", p, str);
		else if (ft_strcmp_split(&str[p->first], "||") == 1)
			er = many_operators(my_list, "||", p, str);
		else if (ft_strcmp_split(&str[p->first], ";;") == 1)
			er = many_operators(my_list, ";;", p, str);
		else if (ft_strcmp_split(&str[p->first], ">>") == 1)
			er = what_i_seek(my_list, ">>", p, str);
		else if (ft_strcmp_split(&str[p->first], "<") == 1)
			what_i_seek(my_list, "<", p, str);
		else if (ft_strcmp_split(&str[p->first], ">") == 1)
			what_i_seek(my_list, ">", p, str);
		else if (ft_strcmp_split(&str[p->first], ";") == 1)
			er = what_i_seek(my_list, ";", p, str);
		else if (ft_strcmp_split(&str[p->first], "|") == 1)
			er = what_i_seek(my_list, "|", p, str);
		else if (ft_strcmp_split(&str[p->first], " ") == 1)
			what_i_seek(my_list, " ", p, str);
	}
	return (er);
}

static int		ft_split_1(char *str, t_pair p, t_list **list)
{
	int	error;
	t_pair p1;

	p1.first = 0;
	p1.second = 0;
	while (str[++(p.first)] != 0)
	{
		if (str[p.first] == '\"' && p1.second % 2 == 0)
			p1.first++;
		if (str[p.first] == '\'' && p1.first % 2 == 0)
			p1.second++;
		error = ft_split_norm(list, str, &p, 0, p1);
		if (error == -1)
		{
			free_full_list(list);
			free_if_exist(str);
			return (-1);
		}
		else if (error == -2)
			break ;
		else if (error == 1)
			p.first++;
	}
	if (error != -2)
		if (p.second != p.first)
			ft_lstadd_back(list, \
			ft_lstnew(ft_strndup(&str[p.second], p.first - p.second)));
	return (0);
}

t_list			*ft_split(char const *str_bed, t_list *list)
{
	t_pair		p;
	char		*str;

	p.first = -1;
	p.second = 0;
	str = ft_strtrim(str_bed, " ");
	if (*str == 0)
		return (0);
	if (ft_split_1(str, p, &list) == -1)
		return (NULL);
	free_if_exist(str);
	str = ft_split_2(list, str);
	if (str != 0)
		ft_lstadd_back(&list, ft_split(str, 0));
	return (list);
}
