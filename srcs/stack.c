/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:54:52 by rnancee           #+#    #+#             */
/*   Updated: 2021/03/19 12:54:53 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push(t_stack **stack, int data)
{
	t_stack	*new;

	if (!(new = malloc(sizeof(t_stack))))
		return ;
	new->data = data;
	new->next = 0;
	if (*stack)
		new->next = *stack;
	*stack = new;
}

int		pop(t_stack **stack)
{
	t_stack	*temp;
	int		result;

	if (!stack || !(*stack))
		return (-1);
	temp = *stack;
	result = (*stack)->data;
	*stack = (*stack)->next;
	if (temp)
		free(temp);
	return (result);
}
