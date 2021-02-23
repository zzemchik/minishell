/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmass <rmass@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 19:41:42 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/20 16:43:36 by rmass            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*temp;

	i = -1;
	temp = (char *)s;
	while (temp[0] != 0 || c == 0)
	{
		if (temp[0] == c)
			return (temp);
		temp++;
	}
	return (0);
}

char	*ft_strndup(const char *str, int kk)
{
	char	*str_cpy;
	size_t	i;

	if (str == 0)
		return (0);
	i = ft_strlen(str);
	if (kk < i)
		i = kk;
	if (!(str_cpy = (char *)malloc(i + 1)))
		exita();
	str_cpy[i] = 0;
	i = -1;
	while (str[++i] != 0 && kk != 0)
	{
		str_cpy[i] = str[i];
		kk--;
	}
	return (str_cpy);
}

int		is_alpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int		is_num(char c)
{
	return (c >= '0' && c <= '9');
}

void	free_if_exist(char *str)
{
	if (str)
		free(str);
}
