/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standart_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 17:28:20 by rmass             #+#    #+#             */
/*   Updated: 2021/02/23 17:30:30 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*res;

	if (s == 0)
		return (0);
	if (ft_strlen(s) <= start)
		return (ft_strdup(""));
	if (!(res = malloc(len + 1)))
		return (0);
	res[len] = 0;
	i = -1;
	while (++i < (int)len)
		res[i] = s[start + i];
	res[i] = 0;
	return (res);
}

char	**fr(char **arr)
{
	while (*arr)
	{
		free(*arr);
		arr++;
	}
	free(arr);
	return (0);
}

char	**standart_split(char const *s, char c)
{
	int		count;
	int		i;
	int		j;
	char	**res;

	count = 1;
	i = -1;
	while (s && s[++i])
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
	i = -1;
	if (!s || !(res = malloc(sizeof(char*) * count)))
		return (0);
	res[count - 1] = 0;
	count = -1;
	while (s[++i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j = i;
		if (s[i] != c && (s[i + 1] == 0 || s[i + 1] == c))
			if (!(res[++count] = ft_substr(s, j, i - j + 1)))
				return (fr(res));
	}
	return (res);
}
