#include "minishell.h"

static char	*find_new_line_mini(char *buff)
{
	int i;

	i = -1;
	while (buff[++i] != 0)
		if (buff[i] == '\n')
			return (ft_strdup(&buff[i + 1]));
	return (0);
}

static void	is_str(char **temp, char **after_n, char **line, char **str)
{
	*temp = *after_n;
	*after_n = find_new_line_mini(*str);
	if (*temp)
		free(*temp);
	*temp = *line;
	*line = ft_strjoin(*line, *str);
	if (*temp)
		free(*temp);
	free(*str);
	*str = ft_strdup(*after_n);
}

static int	some_read(char **buff, char **line, char **after_n, int fd)
{
	int		count;
	char	*temp;

	count = 1;
	while (count > 0)
	{
		count = read(fd, *buff, 100);
		(*buff)[count] = 0;
		temp = *after_n;
		*after_n = find_new_line_mini(*buff);
		if (temp)
			free(temp);
		temp = *line;
		*line = ft_strjoin(*line, *buff);
		if (temp)
			free(temp);
		if (*after_n != 0)
			break ;
	}
	return (count);
}

static int	some_func(char **str, char **after_n, char **buff, int count)
{
	free(*str);
	free(*buff);
	*str = ft_strdup(*after_n);
	if (*after_n)
		free(*after_n);
	if (*str == 0 && count == 0)
		return (0);
	if (*str == 0 && count != 0)
		return (-1);
	return (1);
}

int			get_next_line_mini(int fd, char **line)
{
	static char	*str[1024];
	int			c;
	char		*after_n;
	char		*temp;
	char		*buff;

	buff = malloc(101);
	c = 1;
	if ((c = read(fd, &c, 0)) == -1 || fd < 0 || line == 0)
		return (-1);
	if ((*line = 0) && !str[fd])
		if (!(str[fd] = ft_strdup("")))
			return (-1);
	if (((after_n = 0) == 0) && str[fd] != 0 && *(str[fd]) != 0)
	{
		is_str(&temp, &after_n, line, &(str[fd]));
		if (after_n)
		{
			free(after_n);
			return (1);
		}
	}
	c = some_read(&buff, line, &after_n, fd);
	return (some_func(&str[fd], &after_n, &buff, c));
}
