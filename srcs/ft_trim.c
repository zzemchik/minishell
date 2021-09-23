#include "minishell.h"

static size_t	scip_beg(size_t i, const char *str_begin, const char *set)
{
	size_t	k;
	int		z;

	k = 0;
	z = 0;
	while (k < i)
	{
		if (set[z] == 0)
			break ;
		if (str_begin[k] == set[z])
		{
			k++;
			z = 0;
		}
		else
			z++;
	}
	return (k);
}

static size_t	scip_end(size_t i, const char *str_begin, const char *set)
{
	int z;

	z = 0;
	while (i)
	{
		if (set[z] == 0)
			break ;
		if (str_begin[i - 1] == set[z])
		{
			i--;
			z = 0;
		}
		else
			z++;
	}
	return (i);
}

char			*ft_strtrim(const char *str_begin, const char *set)
{
	size_t	end;
	size_t	begin;
	int		ii;
	char	*str;

	ii = 0;
	if (str_begin == 0 || set == 0)
		return (0);
	end = ft_strlen(str_begin);
	begin = scip_beg(end, str_begin, set);
	end = scip_end(end, str_begin, set);
	if (end == 0)
		begin = 0;
	if (!(str = (char *)malloc(end - begin + 1)))
		return (0);
	while (end != begin)
		str[ii++] = str_begin[begin++];
	str[ii] = 0;
	return (str);
}
