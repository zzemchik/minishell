/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:58:20 by rmass             #+#    #+#             */
/*   Updated: 2021/03/19 18:17:51 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] != 0)
			i++;
	return (i);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(str1);
	j = ft_strlen(str2);
	if (!(str = (char *)malloc(i + j + 1)))
		return (0);
	i = 0;
	j = 0;
	if (str1 != 0 && (i = -1))
		while (str1[++i] != 0)
			str[i] = str1[i];
	if (str2 != 0 && (j = -1))
		while (str2[++j] != 0)
			str[i + j] = str2[j];
	str[i + j] = 0;
	return (str);
}

void	ft_putstr(const char *str)
{
	if (str)
		write(1, str, ft_strlen(str));
}

int		ft_strcmp(const char *str_f, const char *str_s)
{
	int i;

	i = -1;
	if (str_f == 0 && str_s == 0)
		return (1);
	if (str_f == 0 || str_s == 0)
		return (0);
	while (str_f[++i] != 0 || str_s[i] != 0)
		if (str_f[i] != str_s[i])
			return (0);
	return (1);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		ln;
	int		t;

	ln = (n <= 0) ? 1 : 0;
	t = n;
	while (t != 0)
	{
		t /= 10;
		ln++;
	}
	if (!(res = malloc(ln + 1)))
		return (0);
	if (n == 0)
		res[0] = '0';
	res[ln] = 0;
	if (n < 0)
		res[0] = '-';
	while (n != 0)
	{
		ln--;
		res[ln] = '0' + (n % 10 < 0 ? -(n % 10) : n % 10);
		n /= 10;
	}
	return (res);
}
