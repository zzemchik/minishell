/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:45:46 by rmass             #+#    #+#             */
/*   Updated: 2021/04/03 21:00:55 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_loop_flags(t_list **list)
{
	g_g = 0;
	g_flag = 0;
	if (g_ctrl_c)
	{
		free_full_list(list);
		g_ret_value = 130;
		g_ctrl_c = 0;
	}
	if (g_ctrl_s)
	{
		g_ret_value = 131;
		g_ctrl_s = 0;
	}
}

void	rainbow_putstr(char *str)
{
	int		i;
	char	symb;

	i = -1;
	while (str[++i])
	{
		if (i % 6 == 0)
			ft_putstr(RED);
		if (i % 6 == 1)
			ft_putstr(YELLOW);
		if (i % 6 == 2)
			ft_putstr(GREEN);
		if (i % 6 == 3)
			ft_putstr(CIAN);
		if (i % 6 == 4)
			ft_putstr(BLUE);
		if (i % 6 == 5)
			ft_putstr(MAGENTA);
		symb = str[i];
		write(1, &symb, 1);
	}
	ft_putstr(RESET);
}

void	ctrl_c_handler(int sig)
{
	sig = sig + 0;
	if (g_g)
		return ;
	if (!g_flag)
	{
		write(1, "\b\b  \b\b\n", 7);
		ft_putstr(YELLOW);
		ft_putstr("minishell >> ");
		ft_putstr(RESET);
	}
	g_ctrl_c = 1;
}

void	ctrl_slash_handler(int sig)
{
	sig = sig + 0;
	if (g_g)
		return ;
	if (!g_flag)
		write(1, "\b\b  \b\b", 6);
	g_ctrl_s = 1;
}
