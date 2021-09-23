#include "minishell.h"

void	change_pwd_and_oldpwd(void)
{
	int		ln;
	char	*pwd;
	char	*buf;

	pwd = get_value("PWD", g_vars_list);
	add_var(ft_strdup("OLDPWD"), ft_strdup(pwd), &g_vars_list, 1);
	if (!(buf = malloc(1000)))
		exita(0);
	getcwd(buf, 1000);
	ln = ft_strlen(buf) + 1;
	free_if_exist(buf);
	if (!(buf = malloc(ln)))
		exita(0);
	getcwd(buf, ln);
	add_var(ft_strdup("PWD"), buf, &g_vars_list, 1);
}

void	command_cd(t_list **list, int flag)
{
	if (flag || ((*list)->next && (*list)->next->next \
	&& ft_strcmp((*list)->next->next->data, "|")))
		return ;
	if ((*list)->next)
	{
		free_one_list(list);
		if (chdir((*list)->data) == -1)
		{
			ft_putstr("cd: no such file or directory: ");
			ft_putstr((*list)->data);
			ft_putstr("\n");
			g_ret_value = 1;
		}
		else
			change_pwd_and_oldpwd();
	}
	else
	{
		chdir(get_value("HOME", g_vars_list));
		change_pwd_and_oldpwd();
	}
	skip(list);
}
