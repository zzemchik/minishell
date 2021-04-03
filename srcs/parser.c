/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 18:42:14 by rmass             #+#    #+#             */
/*   Updated: 2021/04/04 01:18:08 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		what_do(t_list **list, t_stack **stack, int flag)
{
	if (ft_strcmp((*list)->data, "pwd") == 1)
		do_it_pwd(list, stack);
	else if (ft_strcmp((*list)->data, "echo"))
		just_do_it(list, stack, &command_echo);
	else if (ft_strcmp((*list)->data, "unset"))
		unset(list);
	else if (ft_strcmp((*list)->data, "export"))
		export(list);
	else if (((*list)->data)[0] == '/' \
	|| (((*list)->data)[0] == '.' && ((*list)->data)[1] == '/'))
		just_do_it(list, stack, &do_bin);
	else if (ft_strcmp((*list)->data, "env"))
		parser_env(list, stack);
	else if (ft_strcmp((*list)->data, "enva"))
		parser_enva(list, stack);
	else if (ft_strcmp((*list)->data, "cd"))
		command_cd(list, flag);
	else if (correct_equal((*list)->data))
		apply_equally(list);
	else if (ft_strcmp((*list)->data, "exit"))
		command_exit(list);
	else if ((*list)->data[0] != 0 && cheker_kalla(list) == 1)
		just_do_it(list, stack, &do_bin);
	else
		just_do_it(list, stack, &cnf);
}

void		help_execute(t_list **list, t_stack **stack, int flag)
{
	char *str;

	str = find_arrow(*list, 0, 0);
	if (str == NULL)
	{
		ft_putstr("minishell: syntax error near unexpected token 'newline'\n");
		free_full_list(list);
		return ;
	}
	else if (ft_strcmp(str, "kak kakat") == 0)
	{
		ft_putstr("minishell: syntax error near unexpected token \"");
		ft_putstr(str);
		ft_putstr("\"\n");
		free_full_list(list);
		return ;
	}
	kill_arrow(list, 0, 0);
	if (*list)
		what_do(list, stack, flag);
}

void		execute_functions(t_list **list, t_stack **stack, \
								t_pair pair, int **pipefd)
{
	int		my_stdin;
	int		my_stdout;
	t_list	*temp;

	my_stdin = dup(1);
	my_stdout = dup(0);
	if ((temp = *list) && pair.second)
	{
		dup2(pipefd[pair.first - 1][0], 0);
		close(pipefd[pair.first - 1][0]);
	}
	while (temp && !ft_strcmp(temp->data, "|") && !ft_strcmp(temp->data, ";"))
		temp = temp->next;
	if (temp && ft_strcmp(temp->data, "|"))
	{
		dup2(pipefd[pair.first][1], 1);
		close(pipefd[pair.first][1]);
	}
	help_execute(list, stack, pair.second);
	dup2(my_stdin, 1);
	dup2(my_stdout, 0);
	(g_in != 1) ? close(g_in) : 0;
	(g_out != 0) ? close(g_out) : 0;
}

void		parser_loop(t_list **list, t_stack **stack, \
								t_pair *pair, int **pipefd)
{
	replace_vars(*list);
	dequote(*list);
	execute_functions(list, stack, *pair, pipefd);
	free_one_list(list);
	if (*list && ft_strcmp((*list)->data, "|"))
	{
		pair->first++;
		pair->second = 1;
	}
	if (!(*list) || ft_strcmp((*list)->data, ";"))
		while (*stack)
		{
			g_g = 1;
			pop(stack);
			wait(&g_ret_value);
			g_ret_value /= 256;
		}
	parser_loop_flags(list);
	free_one_list(list);
}

void		parser(char *buf)
{
	t_list		*list;
	t_pair		pair;
	int			**pipefd;
	t_stack		*stack;

	list = ft_split(buf, 0);
	if (list && to_many_operator(ft_lstlast(list)->data) == -1)
	{
		free_full_list(&list);
		return ;
	}
	find_tilda(list);
	free_if_exist(buf);
	find_equally(&list);
	give_pipe(list, &pipefd);
	stack = 0;
	pair.first = 0;
	pair.second = 0;
	while (list)
		parser_loop(&list, &stack, &pair, pipefd);
	free_full_list(&list);
	free_pipe(&pipefd);
}
