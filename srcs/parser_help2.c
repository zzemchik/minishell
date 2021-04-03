/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:22:12 by rmass             #+#    #+#             */
/*   Updated: 2021/03/27 23:49:39 by ivan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_bin_norm(char *name, t_list **list)
{
	int		ln;
	int		i;
	t_list	*tmp;
	char	**argv;
	char	**envp;

	ln = 0;
	tmp = *list;
	while (tmp && !ft_strcmp(tmp->data, ";") && !ft_strcmp(tmp->data, "|"))
	{
		ln++;
		tmp = tmp->next;
	}
	argv = malloc(sizeof(char*) * (ln + 1));
	argv[ln] = 0;
	i = -1;
	while (++i < ln)
	{
		argv[i] = ft_strdup((*list)->data);
		free_one_list(list);
	}
	envp = vars_to_array(name);
	free_if_exist(name);
	if (execve(*argv, argv, envp) == -1)
		print_error(*argv);
}

void		do_bin(t_list **list)
{
	char	*temp;
	char	*name;
	char	*value;

	temp = ((*list)->data);
	name = ft_strdup((*list)->data);
	if (((*list)->data)[0] == '.')
	{
		value = give_pwd();
		((*list)->data) = ft_strjoin(value, temp + 1);
		free_if_exist(temp);
	}
	do_bin_norm(name, list);
}

int			to_many_operator(char *str)
{
	if (ft_strcmp(str, ">>>") == 1 || ft_strcmp(str, ";;") == 1 \
	|| ft_strcmp(str, "||") == 1)
	{
		ft_putstr("minishell: syntax error near unexpected token \'");
		write(1, str, 1);
		ft_putstr("\'\n");
		return (-1);
	}
	else if (ft_strcmp(str, ">>>>") == 1)
	{
		ft_putstr("minishell: syntax error near unexpected token \'");
		ft_putstr(">>");
		ft_putstr("\'\n");
		return (-1);
	}
	return (0);
}
