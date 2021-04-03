/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:13:18 by rmass             #+#    #+#             */
/*   Updated: 2021/04/03 21:16:58 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_vars_list(t_env_var *list)
{
	t_env_var	*temp;

	while (list)
	{
		free_if_exist(list->key);
		free_if_exist(list->value);
		temp = list;
		list = list->next;
		free(temp);
	}
}

char	*parse_command(char **line)
{
	int		r;
	char	*str;

	str = 0;
	while (1)
	{
		r = get_next_line_mini(0, line);
		str_new(&str, ft_strjoin(str, *line));
		if (r == 0 && str[0] == 0)
		{
			write(1, "exit\n", 5);
			free(str);
			str = 0;
			break ;
		}
		if (*line && (*line)[ft_strlen(*line) - 1] == '\n')
			break ;
	}
	return (str);
}

int		quote_not_closed(char *str, int *type)
{
	int		i;
	int		in_quote;

	i = -1;
	in_quote = 0;
	while (str[++i])
	{
		if (in_quote && *type == '\"' && str[i] == '\\')
		{
			i++;
			continue ;
		}
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (in_quote && str[i] == *type)
				in_quote = 0;
			else if (!in_quote)
			{
				in_quote = 1;
				*type = str[i];
			}
		}
	}
	return (in_quote);
}

char	*find_quat_1(char *str)
{
	char	*line;
	int		type;

	while (quote_not_closed(str, &type))
	{
		if (type == '\'')
			write(1, "quote> ", 7);
		else
			write(1, "dquote> ", 8);
		line = 0;
		while (!line || line[0] == 0)
			get_next_line_mini(0, &line);
		str_new(&str, ft_strjoin(str, line));
	}
	str_new(&str, ft_strtrim(str, "\n"));
	return (str);
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*str;

	if (argc != 1 && argv)
		return (0);
	all_zero();
	parse_env_vars(envp);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_slash_handler);
	while (1)
	{
		line = 0;
		ft_putstr(YELLOW);
		ft_putstr("minishell >> ");
		ft_putstr(RESET);
		str = parse_command(&line);
		if (!str)
			break ;
		str = find_quat_1(str);
		g_ctrl_c = 0;
		g_ctrl_s = 0;
		parser(str);
		free_if_exist(line);
	}
	exita(1);
}
