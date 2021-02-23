/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:23:00 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/22 18:22:01 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_strcmp_split(const char *str, const char *find)
{
	int i;

	i = -1;
	while (str[++i] != 0 && find[i] != 0)
		if (str[i] != find[i] && str[i] != 0 && find[i] != 0)
			return (0);
	return (1);
}

static void		what_i_seek(t_list **my_list, char *find, t_pair *p, char *str)
{
	if (p->first != p->second)
		ft_lstadd_back(my_list, \
		ft_lstnew(ft_strndup(&str[p->second], p->first - p->second)));
	if (*find != ' ')
		ft_lstadd_back(my_list, ft_lstnew(ft_strdup(find)));
	p->second = p->first + ft_strlen(find);
}

static int find_quat_help(char *line, int *i, char *quat)
{
	int k;

	k = 0;
	if (line[*i] == 0)
		return (k);
	if (line[*i] != 0)
		while (line[++(*i)] != 0)
		{	
			if (line[(*i)] == '\"' && (k = 1) == 1)
				*quat = '\"';
			else if (line[(*i)] == '\'' && (k = 1) == 1)
				*quat = '\'';
		}
	if (line[(*i)] != 0)
		while (line[++(*i)] != 0)
			if (line[(*i)] == *quat && (k = 2) == 2)
				break ;
	if (k == 1)
		return (0);
	return (1);
	
}

static char		*find_quat_two(char quat)
{
	char	*line;
	char	*buf;
	char	*str;
	char	*tmp;
	int		flag;
	int		i;

	str = 0;
	flag = 0;
	buf = malloc(101);
	tmp = str;
	str = ft_strjoin(str, "\n");
	free_if_exist(tmp);

	while (1)
	{
		(quat == '\"') ? ft_putstr("dquote> ") : ft_putstr("quote> ");
		i = -1;
		get_next_line(0, buf, &line);
		tmp = str;
		str = ft_strjoin(str, line);
		free_if_exist(tmp);
		while (line[++i] != 0)
			if (line[i] == quat)
				break ;
		flag = find_quat_help(line, &i, &quat);
		if (flag == 1)
			break ;
		tmp = str;
		str = ft_strjoin(str, "\n");
		free_if_exist(tmp);
		free_if_exist(line);
	}
	free_if_exist(line);
	free_if_exist(buf);
	return (str);
}

static int		find_quat(const char *str, t_pair *p, t_list **list)
{
	char	quat;
	char	*str_tmp;
	char	*str_tmp2;

	str_tmp = 0;
	quat = (str[p->first] == '\"') ? '\"' : '\'';
	while (p->first != 0 && str[p->first] != ' ')
		(p->first)--;
	if (str[p->first] == ' ')
		(p->first)++;
	p->second = p->first;
	while (str[p->first] != quat)
		(p->first)++;
	(p->first)++;
	while (str[p->first] != 0 && str[p->first] != quat)
		(p->first)++;
	if (str[p->first] == 0)
		str_tmp = find_quat_two(quat);
	(p->first)++;
	while (str[p->first] != 0 && str[p->first] != ' ')
		(p->first)++;
	str_tmp2 = ft_strndup(&str[p->second], p->first - p->second);
	ft_lstadd_back(list, ft_lstnew(ft_strjoin(str_tmp2, str_tmp)));
	free_if_exist(str_tmp);
	free_if_exist(str_tmp2);
	p->second = p->first + 1;
	return (0);
}

static void		ft_split_norm(t_list **my_list, char *str, t_pair *p)
{
	if (str[p->first] == '\'' || str[p->first] == '\"')
		find_quat(str, p, my_list);
	else if (ft_strcmp_split(&str[p->first], "<") == 1)
		what_i_seek(my_list, "<", p, str);
	else if (ft_strcmp_split(&str[p->first], ">") == 1 \
	&& str[p->first - 1] != '>')
		what_i_seek(my_list, ">", p, str);
	else if (ft_strcmp_split(&str[p->first], ";") == 1)
		what_i_seek(my_list, ";", p, str);
	else if (ft_strcmp_split(&str[p->first], "|") == 1)
		what_i_seek(my_list, "|", p, str);
	else if (ft_strcmp_split(&str[p->first], " ") == 1)
		what_i_seek(my_list, " ", p, str);
	else if (ft_strcmp_split(&str[p->first], ">>") == 1)
		what_i_seek(my_list, ">>", p, str);
}

t_list			*ft_split(char const *str_bed)
{
	char		*str;
	t_list		*list;
	t_pair		p;

	p.first = -1;
	p.second = 0;
	list = 0;
	str = ft_strtrim(str_bed, " ");
	while (str[++p.first] != 0)
		ft_split_norm(&list, str, &p);
	if (p.second != p.first)
		ft_lstadd_back(&list, \
		ft_lstnew(ft_strndup(&str[p.second], p.first - p.second)));
	free_if_exist(str);
	return (list);
}
