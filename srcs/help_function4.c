/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 18:26:53 by rnancee           #+#    #+#             */
/*   Updated: 2021/03/20 18:37:52 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			free_full_list(t_list **list)
{
	while (*list)
		free_one_list(list);
	return (0);
}

static int	delete_spaces(const char *str)
{
	int find;
	int count;

	find = 1;
	count = 0;
	while (find == 1)
		if (*str == ' ' || *str == '\n' || *str == '\t')
		{
			count++;
			str++;
		}
		else if (*str == '\r' || *str == '\v' || *str == '\f')
		{
			count++;
			str++;
		}
		else
			find = 0;
	return (count);
}

int			ft_atoi(const char *str)
{
	int temp;
	int i;
	int neg;
	int t;

	temp = 0;
	i = 0;
	t = 0;
	neg = 1;
	str += delete_spaces(str);
	if (*str == '+')
		str++;
	else if (*str == '-' && str++)
		neg = -1;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		temp = temp * 10 + str[i] - '0';
		t += (temp != 0) ? 1 : 0;
		if (t > 19)
			return ((neg == 1) ? -1 : 0);
		i++;
	}
	return (temp * neg);
}

int			standart_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (1)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		if (str1[i] == 0 || str2[i] == 0)
			break ;
		i++;
	}
	return (0);
}

void		sort_array(char **arr, int size)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (standart_strcmp(arr[j], arr[j + 1]) == 1)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
