/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 21:19:02 by rmass             #+#    #+#             */
/*   Updated: 2021/04/01 20:26:05 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cnf(t_list **list)
{
	ft_putstr("minishell: command not found: ");
	ft_putstr((*list)->data);
	ft_putstr("\n");
	free_one_list(list);
	while (*list)
	{
		if ((*list)->next && (!(ft_strcmp((*list)->next->data, "|")) || \
		!(ft_strcmp((*list)->next->data, ";"))))
			free_one_list(list);
		else
			break ;
	}
	g_ret_value = 127;
}

void	display_all_varss(void)
{
	t_env_var	*temp;

	temp = g_temp_vars_list;
	while (temp)
	{
		ft_putstr(temp->key);
		ft_putstr("=");
		ft_putstr(temp->value);
		ft_putstr("\n");
		temp = temp->next;
	}
}

void	do_it_pwd(t_list **list, t_stack **stack)
{
	int		pid;
	char	*value;

	value = give_pwd();
	pid = fork();
	if (!pid)
	{
		ft_putstr(value);
		ft_putstr("\n");
		exit(0);
	}
	push(stack, pid);
	skip(list);
}

void	parser_env(t_list **list, t_stack **stack)
{
	int pid;

	if ((*list)->next && !ft_strcmp((*list)->next->data, ";") \
	&& !ft_strcmp((*list)->next->data, "|"))
	{
		ft_putstr("env: ");
		ft_putstr((*list)->next->data);
		ft_putstr(": No such file or directory\n");
		g_ret_value = 127;
	}
	else
	{
		pid = fork();
		if (!pid)
		{
			display_all_vars();
			exit(0);
		}
		push(stack, pid);
	}
	skip(list);
}

void	parser_enva(t_list **list, t_stack **stack)
{
	int pid;

	pid = fork();
	if (!pid)
	{
		display_all_varss();
		exit(0);
	}
	push(stack, pid);
	skip(list);
}
