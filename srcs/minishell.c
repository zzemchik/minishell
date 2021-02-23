/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:57:55 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/23 20:48:55 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exita(void)
{
	exit(0);
}

int		main(int argv, char **argc)
{
	char	*buf;
	char	*line;

	if (argv != 1 || (!(buf = malloc(101))))
		return (0);
	all_zero(argc);
	parse_env_vars(0);
	while (1)
	{
		ft_putstr(YELLOW);
		ft_putstr("minishell >> ");
		ft_putstr(RESET);
		get_next_line(0, buf, &line);
		if (parser(line) == 0)
			break ;
		free_if_exist(line);
	}
	free_if_exist(buf);
}
