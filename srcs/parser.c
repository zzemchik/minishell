/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 15:32:12 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/23 17:40:282 by mnss  e          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cnf(t_list **list)
{
	ft_putstr("minishell: command not found: ");
	ft_putstr((*list)->data);
	ft_putstr("\n");
	free_one_list(list);
	while (list)
	{
		if ((*list)->next && (!(ft_strcmp((*list)->next->data, "|")) || \
		!(ft_strcmp((*list)->next->data, ";"))))
			free_one_list(list);
		else
			break ;
	}
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

void		do_it_pwd(t_list **list, t_stack **stack)
{
	int pid;
	
	pid = fork();
	if (!pid)
	{
		ft_putstr(getcwd(g_current_folder, 1000));
		ft_putstr("\n");
		exita();
	}
	push(stack, pid);
	skip(list);
}

void		parser_env(t_list **list, t_stack **stack)
{
	int pid;
		
	pid = fork();
	if (!pid)
	{
		display_all_vars();
		exita();
	}
	push(stack, pid);
	skip(list);
}

void		parser_enva(t_list **list, t_stack **stack)
{
	int pid;
		
	pid = fork();
	if (!pid)
	{
		display_all_varss();
		exita();
	}
	push(stack, pid);
	skip(list);
}

void	just_do_it(t_list **list, t_stack **stack, void (*f)(t_list **list))
{
	int	pid;
	
	pid = fork();
	if (!pid)
	{
		if (f)
			f(list);
		exita();
	}
	push(stack, pid);
	skip(list);
}

void	execute_functions(t_list **list, t_stack **stack)
{
	int pid;
	
	g_flag_write = ((*stack) == 0) ? 1 : 0;
	if (ft_strcmp((*list)->data, "pwd") == 1)
		do_it_pwd(list, stack);
	else if (ft_strcmp((*list)->data, "echo"))
		just_do_it(list, stack, &command_echo);
	else if (ft_strcmp((*list)->data, "unset"))
		unset(list);
	else if (ft_strcmp((*list)->data, "export"))
		export(list);
	else if (ft_strcmp((*list)->data, "env"))
		parser_env(list, stack);
	else if (ft_strcmp((*list)->data, "enva"))
		parser_enva(list, stack);
	else if (ft_strcmp((*list)->data, "cd"))
		just_do_it(list, stack, &command_cd);
	else if (apply_equally(list))
		just_do_it(list, stack, NULL);
	else if (ft_strcmp((*list)->data, "exit"))
		exita();
	else
		just_do_it(list, stack, &cnf);
}
int		parser(const char *buf)
{
	t_list		*list;
	int			pid;
	t_stack	*stack;

	list = ft_split(buf);
	find_equally(list);
	replace_vars(list);
	dequote(list);
	stack = 0;
	while (list)
	{
		execute_functions(&list, &stack);
		free_one_list(&list);
		if (!list || ft_strcmp(list->data, ";"))
			while (stack)
			{
				pid = pop(&stack);
				wait(&pid);
			}
		free_one_list(&list);
		g_flag_write = 1;
	}
	free(list);
	
	return (1);
}

// int main(int argc, char *argv[])
// {
// 	int pipefd[2];
// 	pid_t pid;
// 	char buf;

// 	assert(argc == 2);

// 	pipe(pipefd);
// 	pid = fork(); 
//     if (!pid) 
// 	{
// 		close(pipefd[1]);

// 		while (read(pipefd[0], &buf, 1) > 0)
// 			write(STDOUT_FILENO, &buf, 1);
// 		write(STDOUT_FILENO, "\n", 1);
// 		close(pipefd[0]);
// 		exit(0);

// 	}
// 	close(pipefd[0]); 
// 	write(pipefd[1], argv[1], strlen(argv[1]));
// 	close(pipefd[1]);
// 	wait(NULL);
// 	exit(0);
// }