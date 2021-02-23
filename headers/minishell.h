/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnancee <rnancee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:58:35 by rnancee           #+#    #+#             */
/*   Updated: 2021/02/23 20:48:55 by rnancee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RESET		"\033[0m"
# define BLACK		"\033[1;30m"
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BLUE		"\033[1;34m"
# define MAGENTA	"\033[1;35m"
# define CIAN		"\033[1;36m"
# define WHITE		"\033[1;37m"

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <time.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct			s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct			s_list
{
	char				*data;
	struct s_list		*next;
}						t_list;

typedef struct			s_list_int
{
	int					data;
	struct s_list		*next;
}						t_list_int;

typedef struct			s_stack
{
	int					data;
	struct s_stack		*next;
}						t_stack;

typedef struct			s_pair
{
	int					first;
	int					second;
}						t_pair;

int						g_ret_value;
char					g_flag_write;
char					*g_current_folder;
t_env_var				*g_vars_list;
t_env_var				*g_temp_vars_list;

void					exita(void);
int						is_num(char c);
char					*ft_itoa(int n);
int						is_alpha(char c);
void					cnf(t_list **list);
void					skip(t_list **list);
void					save_env_vars(void);
void					unset(t_list **list);
int						pop(t_stack **stack);
void					parse_env_vars(int i);
void					export(t_list **list);
void					dequote(t_list *list);
void					all_zero(char **argc);
void					display_all_vars(void);
int						parser(const char *buf);
int						ft_lstsize(t_list *lst);
t_list					*ft_lstlast(t_list *lst);
void					free_if_exist(char *str);
void					print_list(t_list *list);
void					command_cd(t_list **list);
t_list					*ft_lstnew(char *content);
int						ft_strlen(const char *str);
void					ft_putstr(const char *str);
char					*find_new_line(char *buff);
void					replace_vars(t_list *list);
void					find_equally(t_list *list);
t_list_int				*ft_lstnew_int(int content);
char					*ft_strdup(const char *str);
void					command_echo(t_list **list);
int						apply_equally(t_list **list);
void					free_one_list(t_list **list);
t_list					*ft_split(char const *str_bed);
int						ft_lstsize_int(t_list_int *lst);
void					push(t_stack **stack, int data);
t_list_int				*ft_lstlast_int(t_list_int *lst);
char					*ft_strchr(const char *s, int c);
char					*ft_strndup(const char *str, int kk);
t_list_int				*lst_int_push_front(t_list_int **lst);
char					*get_value(char *key, t_env_var *vars);
char					**standart_split(char const *s, char c);
void					remove_value(t_env_var **list, char *key);
int						check_last_dollar(char *temp, char **result);
char					*ft_strtrim(char const *s1, char const *set);
void					ft_lstadd_back(t_list **lst, t_list *lst_new);
int						get_next_line(int fd, char *buff, char **line);
int						ft_strcmp(const char *str_f, const char *str_s);
char					*ft_strjoin(const char *str1, const char *str2);
void					add_var(char *key, char *value, t_env_var **list);
void					ft_lstadd_back_int(t_list_int **lst, t_list_int *lst_new);

#endif
